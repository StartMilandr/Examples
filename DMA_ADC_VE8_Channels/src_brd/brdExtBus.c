#include <MDR32F9Qx_port.h>
#include <MDR32F9Qx_rst_clk.h>
#include <MDR32F9Qx_ebc.h>

#include "brdDef.h"

void BRD_ExtBus_Init (void)
{
	EBC_InitTypeDef EBC_InitStruct;

	/* Enables the HSI clock on ExtBus */
  RST_CLK_PCLKcmd(RST_CLK_PCLK_EBC, ENABLE);		
	
	EBC_DeInit();
	EBC_StructInit(&EBC_InitStruct);
  EBC_InitStruct.EBC_Mode       = EBC_MODE_RAM;
	EBC_InitStruct.EBC_WaitState  = EBC_WAIT_STATE_3HCLK; //EBC_WAIT_STATE_18HCLK; //EBC_WAIT_STATE_11HCLK;
	EBC_Init(&EBC_InitStruct);
}

void BRD_ExtBus_InitPins_A20_D32 (void)
{	
	PORT_InitTypeDef PortInitStruc;	
	
  //  Clock to PORTs
	RST_CLK_PCLKcmd(BRD_EBS_A20_D32_CLK, ENABLE);
	
  //  Stuct Init by default
  PORT_StructInit(&PortInitStruc);
  PortInitStruc.PORT_MODE = PORT_MODE_DIGITAL;
  PortInitStruc.PORT_SPEED = PORT_SPEED_FAST;	

  //  DATA PINs Init
  PortInitStruc.PORT_Pin  = BRD_EBC_DATA_PORT_LO16_PINS;
	PortInitStruc.PORT_FUNC = BRD_EBC_DATA_PORT_LO16_FUNC;
  PORT_Init(BRD_EBC_DATA_PORT_LO16, &PortInitStruc);	
  
  PortInitStruc.PORT_Pin  = BRD_EBC_DATA_PORT_HI16_PINS;
	PortInitStruc.PORT_FUNC = BRD_EBC_DATA_PORT_HI16_FUNC;
  PORT_Init(BRD_EBC_DATA_PORT_HI16, &PortInitStruc);	  

  //  ADDR PINs Init  
  PortInitStruc.PORT_Pin  = BRD_EBC_PORT_ADDR20_PINS;
	PortInitStruc.PORT_FUNC = BRD_EBC_PORT_ADDR20_FUNC;
  PORT_Init(BRD_EBC_PORT_ADDR20, &PortInitStruc);	  

#ifdef BRD_EBC_PORT_ADDR20_1_USED
  PortInitStruc.PORT_Pin  = BRD_EBC_PORT_ADDR20_1_PINS;
	PortInitStruc.PORT_FUNC = BRD_EBC_PORT_ADDR20_1_FUNC;
  PORT_Init(BRD_EBC_PORT_ADDR20_1, &PortInitStruc);	  
#endif

#ifdef BRD_EBC_PORT_ADDR20_2_USED
  PortInitStruc.PORT_Pin  = BRD_EBC_PORT_ADDR20_2_PINS;
	PortInitStruc.PORT_FUNC = BRD_EBC_PORT_ADDR20_2_FUNC;
  PORT_Init(BRD_EBC_PORT_ADDR20_2, &PortInitStruc);	  
#endif

  //  CTRL PINs Init  
  PortInitStruc.PORT_Pin  = BRD_EBC_PORT_CTRL_PINS;
	PortInitStruc.PORT_FUNC = BRD_EBC_PORT_CTRL_FUNC;
  PORT_Init(BRD_EBC_PORT_CTRL, &PortInitStruc);
  
#ifdef BRD_EBC_PORT_CTRL_1_USED
  //  CTRL PINs Init  
  PortInitStruc.PORT_Pin  = BRD_EBC_PORT_CTRL_1_PINS;
	PortInitStruc.PORT_FUNC = BRD_EBC_PORT_CTRL_1_FUNC;
  PORT_Init(BRD_EBC_PORT_CTRL_1, &PortInitStruc);
#endif
 
}

void BRD_ExtBus_Init_Ready(uint32_t PullUpEna)
{  
	PORT_InitTypeDef PortInitStruc;
  
  //  Stuct Init by default
  PORT_StructInit(&PortInitStruc);
  PortInitStruc.PORT_MODE = PORT_MODE_DIGITAL;
  PortInitStruc.PORT_SPEED = PORT_SPEED_FAST;  
  
	//	PF0 - Ready  
	PortInitStruc.PORT_Pin   = (PORT_Pin_0);  
  PortInitStruc.PORT_OE    = PORT_OE_IN;
	PortInitStruc.PORT_FUNC  = PORT_FUNC_ALTER;
  PortInitStruc.PORT_PULL_DOWN = PORT_PULL_DOWN_ON;  // Not Ready PullUp
  
	PORT_Init(MDR_PORTF, &PortInitStruc);
}

//void BRD_ExtBus_InitPins_A20_D32 (void)
//{	
//	PORT_InitTypeDef PortInit;	
//	
//	/* Enables the clock on PORTA */
//	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTA, ENABLE);
//	/* Enables the clock on PORTB */
//	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTB, ENABLE);	
//    /* Enables the clock on PORTC */
//	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTC, ENABLE);
//	/* Enables the clock on PORTE */
//	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTE, ENABLE);
//	/* Enables the HSI clock on PORTF */
//  RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTF, ENABLE);
//	
//	//	Port Struct init for Out	
//	PortInit.PORT_MODE  		= PORT_MODE_DIGITAL;
//	PortInit.PORT_PD 				= PORT_PD_DRIVER;
//  PortInit.PORT_PD_SHM 		= PORT_PD_SHM_OFF;	
//	//PortInit.PORT_SPEED 		= PORT_SPEED_SLOW; 
//		PortInit.PORT_SPEED = PORT_SPEED_FAST;	
//	PortInit.PORT_GFEN 			= PORT_GFEN_OFF;
//	PortInit.PORT_PULL_UP 	= PORT_PULL_UP_OFF;
//  PortInit.PORT_PULL_DOWN = PORT_PULL_DOWN_OFF;
//	
//	PortInit.PORT_OE    = PORT_OE_OUT;
//	PortInit.PORT_FUNC  = PORT_FUNC_MAIN;

//	//	PF2-PF15 => ADDR[2..15]
//	PortInit.PORT_Pin   = (PORT_Pin_2 | PORT_Pin_3 | PORT_Pin_4 | PORT_Pin_5 | 
//												 PORT_Pin_6 | PORT_Pin_7 | PORT_Pin_8 | PORT_Pin_9 | 
//												 PORT_Pin_10 | PORT_Pin_11 | PORT_Pin_12 | PORT_Pin_13 | PORT_Pin_14 | PORT_Pin_15);
//	PORT_Init(MDR_PORTF, &PortInit);	
//	
//	//	PE0-PE3 => ADDR[16..19]
//	PortInit.PORT_Pin   = (PORT_Pin_0 | PORT_Pin_1 | PORT_Pin_2 | PORT_Pin_3);
//	PORT_Init(MDR_PORTE, &PortInit);

//  // PA0-PA15 => DATA[0..15]
//	PortInit.PORT_Pin   = PORT_Pin_All;
//	PORT_Init(MDR_PORTA, &PortInit);

//  // PB0-PB15 => DATA[16..31]
//	PortInit.PORT_Pin   = PORT_Pin_All;
//	PORT_Init(MDR_PORTB, &PortInit);

//  //PC1 => OE, PC2 => WE, PC3-PC6 => BE0 - BE3
//	PortInit.PORT_Pin   = (PORT_Pin_1 | PORT_Pin_2 | PORT_Pin_3 | PORT_Pin_4 | PORT_Pin_5 | PORT_Pin_6);
//	PORT_Init(MDR_PORTC, &PortInit);	
//  
//  
//	//	PF0 - Ready  
//	PortInit.PORT_Pin   = (PORT_Pin_0);  
//  PortInit.PORT_OE    = PORT_OE_IN;
//	PortInit.PORT_FUNC  = PORT_FUNC_ALTER;
//	PortInit.PORT_PULL_UP 	= PORT_PULL_UP_OFF;
//  PortInit.PORT_PULL_DOWN = PORT_PULL_DOWN_ON; //FF;
//  
//	PORT_Init(MDR_PORTF, &PortInit);	
//  
//}


