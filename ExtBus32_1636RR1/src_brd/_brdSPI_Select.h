#ifndef BRD_SPI_SELECT_H
#define BRD_SPI_SELECT_H

#include "brdDef.h"
#include "brdSPI.h"

#if defined (USE_MDR1986VE1T)

//  SPI1 Select Pins
  #define  BRD_SPI1_PORT_CLK         BRD_SPI1_D_PORT_CLK 
  #define  BRD_SPI1_PORT             BRD_SPI1_D_PORT
  #define  BRD_SPI1_PINS             BRD_SPI1_D_PINS
  #define  BRD_SPI1_PINS_FUNC        BRD_SPI1_D_PINS_FUNC
  #define  BRD_SPI1_PINS_FUNC_CLEAR  BRD_SPI1_D_PINS_FUNC_CLEAR      
  
  #define  BRD_SPI1_CLOCK            RST_CLK_PCLK_SSP1
  #define  BRD_SPI1                  MDR_SSP1

//  SPI2 Select Pins
  #define  BRD_SPI2_PORT_CLK         BRD_SPI2_D_PORT_CLK 
  #define  BRD_SPI2_PORT             BRD_SPI2_D_PORT
  #define  BRD_SPI2_PINS             BRD_SPI2_D_PINS
  #define  BRD_SPI2_PINS_FUNC        BRD_SPI2_D_PINS_FUNC
  #define  BRD_SPI2_PINS_FUNC_CLEAR  BRD_SPI2_D_PINS_FUNC_CLEAR      
  
  #define  BRD_SPI2_CLOCK            RST_CLK_PCLK_SSP2
  #define  BRD_SPI2                  MDR_SSP2
  
#elif defined (USE_MDR1986VE9x)

//  SPI1 Pins Select
  #define  BRD_SPI1_PORT_CLK         BRD_SPI1_F_PORT_CLK 
  #define  BRD_SPI1_PORT             BRD_SPI1_F_PORT
  #define  BRD_SPI1_PINS             BRD_SPI1_F_PINS
  #define  BRD_SPI1_PINS_FUNC        BRD_SPI1_F_PINS_FUNC 
  #define  BRD_SPI1_PINS_FUNC_CLEAR  BRD_SPI1_F_PINS_FUNC_CLEAR
  
  #define  BRD_SPI1_CLOCK            RST_CLK_PCLK_SSP1
  #define  BRD_SPI1                  MDR_SSP1
    
//  SPI2 Pins Select    
  #define  BRD_SPI2_PORT_CLK         BRD_SPI2_D_PORT_CLK 
  #define  BRD_SPI2_PORT             BRD_SPI2_D_PORT
  #define  BRD_SPI2_PINS             BRD_SPI2_D_PINS
  #define  BRD_SPI2_PINS_FUNC        BRD_SPI2_D_PINS_FUNC 
  #define  BRD_SPI2_PINS_FUNC_CLEAR  BRD_SPI2_D_PINS_FUNC_CLEAR    
  
  #define  BRD_SPI2_CLOCK            RST_CLK_PCLK_SSP2
  #define  BRD_SPI2                  MDR_SSP2
    
#endif

//  Traffic settings
SSP_InitTypeDef _SSPInitStruct = 
{
  .SSP_SCR        = 0,                         //  SSP_SCR - Фактор скорости передачи данных  
  .SSP_CPSDVSR    = 12,                        //  SSP_CPSDVSR - Предделитель тактовой частоты
  .SSP_Mode       = SSP_ModeMaster,             //  SSP_Mode
  .SSP_WordLength = SSP_WordLength8b,           //  SSP_WordLength - Длина кадра

  .SSP_SPH        = SSP_SPH_1Edge,              //  SSP_SPH  - Фаза тактового сигнала
  .SSP_SPO        = SSP_SPO_Low,                //  SSP_SPO  - Полярность тактовых импульсов
  .SSP_FRF        = SSP_FRF_SPI_Motorola,       //  SSP_FRF  - Протокол передачи данных
  
  .SSP_HardwareFlowControl = SSP_HardwareFlowControl_SSE    // SSP_HardwareFlowControl - Аппаратное управление передачей данных
  //.SSP_HardwareFlowControl = SSP_HardwareFlowControl_LBM  // тестовый режим - выход на вход
};


BRD_SPI_Obj  BRD_SPI1_Obj = {
  //  Pins Init
  .PORTx          = BRD_SPI1_PORT,            //  MDR_PORT_TypeDef*
  .Port_ClockMask = BRD_SPI1_PORT_CLK,        //  uint32_t 
  .Port_PinsSel   = BRD_SPI1_PINS,            //  uint32_t
  .Port_PinsFunc  = BRD_SPI1_PINS_FUNC,       //  PORT_FUNC_TypeDef
  .Port_PinsFunc_ClearMask = BRD_SPI1_PINS_FUNC_CLEAR, //  uint32_t
  //  SPI Init
  .SPIx           = BRD_SPI1,                 //  MDR_SSP_TypeDef*
  .SPI_ClockMask  = BRD_SPI1_CLOCK,           //  uint32_t
  //  SPI Struct
  .pSSPInitStruct = &_SSPInitStruct           //  SSP_InitTypeDef*
};

BRD_SPI_Obj  BRD_SPI2_Obj = {
  //  Pins Init
  .PORTx          = BRD_SPI2_PORT,            //  MDR_PORT_TypeDef*
  .Port_ClockMask = BRD_SPI2_PORT_CLK,        //  uint32_t 
  .Port_PinsSel   = BRD_SPI2_PINS,            //  uint32_t
  .Port_PinsFunc  = BRD_SPI2_PINS_FUNC,       //  PORT_FUNC_TypeDef
  .Port_PinsFunc_ClearMask = BRD_SPI2_PINS_FUNC_CLEAR, //  uint32_t
  //  SPI Init
  .SPIx           = BRD_SPI2,                 //  MDR_SSP_TypeDef*
  .SPI_ClockMask  = BRD_SPI2_CLOCK,           //  uint32_t
  //  SPI Struct
  .pSSPInitStruct = &_SSPInitStruct           //  SSP_InitTypeDef*
};

BRD_SPI_Obj* pBRD_SPI1 = &BRD_SPI1_Obj;
BRD_SPI_Obj* pBRD_SPI2 = &BRD_SPI2_Obj;


#endif //BRD_SPI_SELECT_H
