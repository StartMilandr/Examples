#include "brdSPI.h"
#include "brdDef.h"


// Конфигурация линий ввода-вывода
void BRD_SPI_PortInit (BRD_SPI_Obj* BRD_SPI)
{
  // Структура для инициализации линий ввода-вывода
  PORT_InitTypeDef GPIOInitStruct;

  // Разрешение тактирования порта
  RST_CLK_PCLKcmd (BRD_SPI->Port_ClockMask, ENABLE);	
	
  // Общая конфигурация линий ввода-вывода
  GPIOInitStruct.PORT_PULL_UP   = PORT_PULL_UP_OFF;
  GPIOInitStruct.PORT_PULL_DOWN = PORT_PULL_DOWN_OFF;
  GPIOInitStruct.PORT_PD_SHM    = PORT_PD_SHM_OFF;
  GPIOInitStruct.PORT_PD        = PORT_PD_DRIVER;
  GPIOInitStruct.PORT_GFEN      = PORT_GFEN_OFF;
  GPIOInitStruct.PORT_SPEED     = PORT_SPEED_MAXFAST;
  GPIOInitStruct.PORT_MODE      = PORT_MODE_DIGITAL;

  // Инициализация выводов
  GPIOInitStruct.PORT_Pin     = BRD_SPI->Port_PinsSel;
  GPIOInitStruct.PORT_FUNC    = BRD_SPI->Port_PinsFunc;  
  
  PORT_Init (BRD_SPI->PORTx, &GPIOInitStruct);
}

void BRD_SPI_Init(BRD_SPI_Obj* BRD_SPI, uint32_t isMaster)
{
  // Тактирование
	RST_CLK_PCLKcmd(BRD_SPI->SPI_ClockMask, ENABLE);	
	
  // Деинициализация модуля SSP1
  SSP_DeInit (BRD_SPI->SPIx);

  // Выбор предделителя тактовой частоты для модуля SSP1
  SSP_BRGInit (BRD_SPI->SPIx, SSP_HCLKdiv1);

  // Выбор Мастер - Ведомый
  if (isMaster)
    BRD_SPI->pSSPInitStruct->SSP_Mode = SSP_ModeMaster;
  else
    BRD_SPI->pSSPInitStruct->SSP_Mode = SSP_ModeSlave;

  // Инициализация модуля SSP1
  SSP_Init (BRD_SPI->SPIx, BRD_SPI->pSSPInitStruct);

  // Включение модуля SSP1
  SSP_Cmd (BRD_SPI->SPIx, ENABLE);
	
	//	Wait FIFO TX empty
	while (SSP_GetFlagStatus(BRD_SPI->SPIx, SSP_FLAG_TFE) != SET);
  BRD_SPI_ClearFIFO_RX(BRD_SPI);
}  


void BRD_SPI_SendValue(BRD_SPI_Obj* BRD_SPI, uint16_t value)
{	
	SSP_SendData (BRD_SPI->SPIx, value);
}

uint32_t BRD_SPI_ReadValue(BRD_SPI_Obj* BRD_SPI)
{	
	return SSP_ReceiveData(BRD_SPI->SPIx);
}

uint32_t BRD_SPI_CanSend(BRD_SPI_Obj* BRD_SPI)
{		
	return SSP_GetFlagStatus(BRD_SPI->SPIx, SSP_FLAG_TFE) == SET; // TX buff Empty
}

uint32_t BRD_SPI_CanRead(BRD_SPI_Obj* BRD_SPI)
{	
	return SSP_GetFlagStatus(BRD_SPI->SPIx, SSP_FLAG_RNE) == SET;  // RX buff Not Empty
}

uint16_t BRD_SPI_Master_WRRD(BRD_SPI_Obj* BRD_SPI, uint16_t wrData)  // Return RDValue
{
  //  Send  
  SSP_SendData (BRD_SPI->SPIx, wrData);
  while (SSP_GetFlagStatus (BRD_SPI->SPIx, SSP_FLAG_BSY) == SET);
  //  Read
  return SSP_ReceiveData(BRD_SPI->SPIx);
}

void BRD_SPI_Master_WR(BRD_SPI_Obj* BRD_SPI, uint16_t wrData)
{
  //  Send  
  SSP_SendData (BRD_SPI->SPIx, wrData);
  while (SSP_GetFlagStatus (BRD_SPI->SPIx, SSP_FLAG_BSY) == SET); 
}

uint16_t BRD_SPI_Wait_And_Read(BRD_SPI_Obj* BRD_SPI)  // Return RDValue
{
  while (!BRD_SPI_CanRead(BRD_SPI));
  return SSP_ReceiveData(BRD_SPI->SPIx);
}

void BRD_SPI_Slave_SendNext(BRD_SPI_Obj* BRD_SPI, uint16_t wrNextData)  // Return RDValue
{
  SSP_SendData (BRD_SPI->SPIx, wrNextData);
}


uint16_t BRD_SPI_Slave_RDWR(BRD_SPI_Obj* BRD_SPI, uint16_t wrNextData)  // Return RDValue
{
  uint32_t rdValue;
  //  Read
  rdValue = BRD_SPI_Wait_And_Read(BRD_SPI);
  //  Send NextData
  SSP_SendData (BRD_SPI->SPIx, wrNextData);
  
  return rdValue;
}

void BRD_SPI_FillFIFO_TX(BRD_SPI_Obj* BRD_SPI, uint16_t data)
{
  while (SSP_GetFlagStatus (BRD_SPI->SPIx, SSP_FLAG_TNF) != SET)
  {
    SSP_SendData (BRD_SPI->SPIx, data);
  }  
}

void BRD_SPI_ClearFIFO_RX(BRD_SPI_Obj* BRD_SPI)
{
  while (BRD_SPI_CanRead(BRD_SPI))
    SSP_ReceiveData(BRD_SPI->SPIx);
} 

void BRD_SPI_Wait_ClearFIFO_TX(BRD_SPI_Obj* BRD_SPI)
{
	while (SSP_GetFlagStatus(BRD_SPI->SPIx, SSP_FLAG_TFE) != SET); 
}

void BRD_SPI_Wait_WhileBusy(BRD_SPI_Obj* BRD_SPI)
{
	while (SSP_GetFlagStatus(BRD_SPI->SPIx, SSP_FLAG_BSY) == SET); 
}

void BRD_SPI_ClearFIFO_TX_Slave(BRD_SPI_Obj* BRD_SPI)
{
  uint32_t PORT_OE = BRD_SPI->PORTx->OE;
  uint32_t PORT_FUNC = BRD_SPI->PORTx->FUNC;
  
  //  SPI Disable
  SSP_Cmd (BRD_SPI->SPIx, DISABLE);
  
  //  PINS as Inputs and Ports  
  BRD_SPI->PORTx->OE   &= ~BRD_SPI->Port_PinsSel;
  BRD_SPI->PORTx->FUNC &= BRD_SPI->Port_PinsFunc_ClearMask;
  
  //  SPI To Master
  BRD_SPI_Init(BRD_SPI, 1);  
  
  //  FIFO TX Clear
  BRD_SPI_ClearFIFO_RX(BRD_SPI);
  
  //  SPI To Slave
  BRD_SPI_Init(BRD_SPI, 0);
  
  //  Restore PINS
  BRD_SPI->PORTx->FUNC = PORT_FUNC;
  BRD_SPI->PORTx->OE = PORT_OE;
}

 
