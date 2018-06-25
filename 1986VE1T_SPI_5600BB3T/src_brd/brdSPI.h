#ifndef BRD_SPI_H
#define BRD_SPI_H

#include <MDR32F9Qx_port.h>
#include <MDR32F9Qx_rst_clk.h>
#include <MDR32F9Qx_ssp.h>


//  SPI Настройки обмена
#define SPI_DATA_L    SSP_WordLength8b
#define SPI_SCR       5                            // Фактор скорости передачи данных
#define SPI_CPSDVSR   100                          // Предделитель тактовой частоты

//#define SPI_FLOW_CTRL 		SSP_HardwareFlowControl_LBM
#define SPI_FLOW_CTRL 		SSP_HardwareFlowControl_SSE

typedef struct {
  //  Pins Init
  MDR_PORT_TypeDef* PORTx;
  uint32_t          Port_ClockMask; 
  uint32_t          Port_PinsSel;
  PORT_FUNC_TypeDef Port_PinsFunc;
  uint32_t          Port_PinsFunc_ClearMask;
  //  SPI Init
  MDR_SSP_TypeDef*  SPIx;
  uint32_t          SPI_ClockMask;
  //uint32_t          IsMaster;
  //  SPI Struct
  SSP_InitTypeDef*  pSSPInitStruct;
} BRD_SPI_Obj;

 
  
//  Init
void BRD_SPI_PortInit (BRD_SPI_Obj* BRD_SPI);
void BRD_SPI_Init(BRD_SPI_Obj* BRD_SPI, uint32_t isMaster);

//  Basic Transfer
void BRD_SPI_SendValue(BRD_SPI_Obj* BRD_SPI, uint16_t value);
uint32_t BRD_SPI_ReadValue(BRD_SPI_Obj* BRD_SPI);
uint32_t BRD_SPI_CanSend(BRD_SPI_Obj* BRD_SPI);
uint32_t BRD_SPI_CanRead(BRD_SPI_Obj* BRD_SPI);

//  Write-Read for master - slave
uint16_t BRD_SPI_Wait_And_Read(BRD_SPI_Obj* BRD_SPI);                       // Return RDValue
uint16_t BRD_SPI_Master_WRRD(BRD_SPI_Obj* BRD_SPI, uint16_t wrData);        // Return RDValue
void BRD_SPI_Master_WR(BRD_SPI_Obj* BRD_SPI, uint16_t wrData);
uint16_t BRD_SPI_Slave_RDWR(BRD_SPI_Obj* BRD_SPI, uint16_t wrNextData);     // Return RDValue
void BRD_SPI_Slave_SendNext(BRD_SPI_Obj* BRD_SPI, uint16_t wrNextData);

//  FIFO 
void BRD_SPI_Wait_ClearFIFO_TX(BRD_SPI_Obj* BRD_SPI);
void BRD_SPI_Wait_WhileBusy(BRD_SPI_Obj* BRD_SPI);

void BRD_SPI_ClearFIFO_TX_Slave(BRD_SPI_Obj* BRD_SPI);
void BRD_SPI_ClearFIFO_RX(BRD_SPI_Obj* BRD_SPI);
void BRD_SPI_FillFIFO_TX(BRD_SPI_Obj* BRD_SPI, uint16_t data);



#endif //BRD_SPI_H
