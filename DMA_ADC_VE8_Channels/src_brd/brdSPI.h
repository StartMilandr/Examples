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
} SPI_Obj;

 
  
//  Init
void BRD_SPI_PortInit (SPI_Obj* BRD_SPI);
void BRD_SPI_Init(SPI_Obj* BRD_SPI, uint32_t isMaster);

//  Basic Transfer
void BRD_SPI_SendValue(SPI_Obj* BRD_SPI, uint16_t value);
uint32_t BRD_SPI_ReadValue(SPI_Obj* BRD_SPI);
uint32_t BRD_SPI_CanSend(SPI_Obj* BRD_SPI);
uint32_t BRD_SPI_CanRead(SPI_Obj* BRD_SPI);

//  Write-Read for master - slave
uint16_t BRD_SPI_Wait_And_Read(SPI_Obj* BRD_SPI);                       // Return RDValue
uint16_t BRD_SPI_Master_WRRD(SPI_Obj* BRD_SPI, uint16_t wrData);        // Return RDValue
void BRD_SPI_Master_WR(SPI_Obj* BRD_SPI, uint16_t wrData);
uint16_t BRD_SPI_Slave_RDWR(SPI_Obj* BRD_SPI, uint16_t wrNextData);     // Return RDValue
void BRD_SPI_Slave_SendNext(SPI_Obj* BRD_SPI, uint16_t wrNextData);

//  FIFO 
void BRD_SPI_WAIT_FIFO_TX_Clear(SPI_Obj* BRD_SPI);
void BRD_SPI_FIFO_TX_Clear_Slave(SPI_Obj* BRD_SPI);
void BRD_SPI_FIFO_RX_Clear(SPI_Obj* BRD_SPI);


#endif //BRD_SPI_H
