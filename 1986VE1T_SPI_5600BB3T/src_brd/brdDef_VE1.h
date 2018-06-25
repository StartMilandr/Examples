#ifndef _BRD_DEF_VE1
#define _BRD_DEF_VE1

#ifdef USE_MDR1986VE1T

//  --------------  Buttons Definition  ------------
    #define BRD_BTN_PORT_SEL       MDR_PORTE
    #define BRD_BTN_PIN_SEL        PORT_Pin_9

    #define BRD_BTN_PORT_UP        MDR_PORTE
    #define BRD_BTN_PIN_UP         PORT_Pin_8
	
    #define BRD_BTN_PORT_RIGHT     MDR_PORTE
    #define BRD_BTN_PIN_RIGHT      PORT_Pin_5
	
    #define BRD_BTN_PORT_DOWN      MDR_PORTE
    #define BRD_BTN_PIN_DOWN       PORT_Pin_15
	
    #define BRD_BTN_PORT_LEFT      MDR_PORTE
    #define BRD_BTN_PIN_LEFT       PORT_Pin_10
	
    #define BRD_BTN_PORT_BACK      MDR_PORTE
    #define BRD_BTN_PIN_BACK       PORT_Pin_11	

    // for Initialization
    #define BRD_BTNs_PORT_CLK      RST_CLK_PCLK_PORTE
    #define BRD_BTNs_PORT_MASK     MDR_PORTE
    #define BRD_BTNs_PIN_MASK      (BRD_BTN_PIN_SEL | BRD_BTN_PIN_UP | BRD_BTN_PIN_RIGHT | BRD_BTN_PIN_DOWN | BRD_BTN_PIN_LEFT | BRD_BTN_PIN_BACK)
    
    //  for Is_BtnAct_...
    #define BRD_BTNs_PUSH_TO_GND


//  ----------    LEDs Definition -------------
    #define BRD_LED_PORT_CLK       RST_CLK_PCLK_PORTD
    #define BRD_LED_PORT           MDR_PORTD
  
    #define BRD_LED_1              PORT_Pin_7
    #define BRD_LED_2              PORT_Pin_8
    #define BRD_LED_3              PORT_Pin_9
    #define BRD_LED_4              PORT_Pin_10
    #define BRD_LED_5              PORT_Pin_11
    #define BRD_LED_6              PORT_Pin_12
    #define BRD_LED_7              PORT_Pin_13
    #define BRD_LED_8              PORT_Pin_14	    
  
    #define BRD_LED_Pins        (BRD_LED_1 | BRD_LED_2 | BRD_LED_3 | BRD_LED_4  \
                               | BRD_LED_5 | BRD_LED_6 | BRD_LED_7 | BRD_LED_8)

//  ----------    SPI Definition -------------
    //  SPI 1
	  #define BRD_SPI1_D_PIN_CLK	   PORT_Pin_4
	  #define BRD_SPI1_D_PIN_TX		   PORT_Pin_2
	  #define BRD_SPI1_D_PIN_RX		   PORT_Pin_3
	  #define BRD_SPI1_D_PIN_CS		   PORT_Pin_5    

	  #define BRD_SPI1_D_PORT_CLK     RST_CLK_PCLK_PORTD
	  #define BRD_SPI1_D_PORT			    MDR_PORTD
    #define BRD_SPI1_D_PINS         (BRD_SPI1_D_PIN_CLK | BRD_SPI1_D_PIN_TX | BRD_SPI1_D_PIN_RX | BRD_SPI1_D_PIN_CS)
    #define BRD_SPI1_D_PINS_FUNC    PORT_FUNC_ALTER
    
    #define BRD_SPI1_D_PINS_FUNC_CLEAR  (~ ((3 << (4 * 2)) | \
                                            (3 << (2 * 2)) | \
                                            (3 << (3 * 2)) | \
                                            (3 << (5 * 2))   \
                                        ))
                                        
    //  SPI 2
	  #define BRD_SPI2_D_PIN_CLK	    PORT_Pin_9
	  #define BRD_SPI2_D_PIN_TX		    PORT_Pin_7
	  #define BRD_SPI2_D_PIN_RX		    PORT_Pin_8
	  #define BRD_SPI2_D_PIN_CS		    PORT_Pin_10    

	  #define BRD_SPI2_D_PORT_CLK     RST_CLK_PCLK_PORTD
	  #define BRD_SPI2_D_PORT			    MDR_PORTD
    #define BRD_SPI2_D_PINS         (BRD_SPI2_D_PIN_CLK | BRD_SPI2_D_PIN_TX | BRD_SPI2_D_PIN_RX | BRD_SPI2_D_PIN_CS)
    #define BRD_SPI2_D_PINS_FUNC    PORT_FUNC_MAIN
    
    #define BRD_SPI2_D_PINS_FUNC_CLEAR  (~ ((3 << (9 * 2)) | \
                                            (3 << (7 * 2)) | \
                                            (3 << (8 * 2)) | \
                                            (3 << (10 * 2))  \
                                        ))                                        

//  ----------    DMA Definition -------------
    #define BRD_DMA_CLOCK_SELECT  (RST_CLK_PCLK_SSP1 | RST_CLK_PCLK_SSP2 | RST_CLK_PCLK_SSP3 |RST_CLK_PCLK_DMA)


//  ----------    ExtBUS Definition -------------
    //  Data: [PA0 .. PA15] = [D0 .. D15]    
    #define BRD_EBC_DATA_PORT_LO8         MDR_PORTA
    #define BRD_EBC_DATA_PORT_LO8_CLK     RST_CLK_PCLK_PORTA
    #define BRD_EBC_DATA_PORT_LO8_PINS    (PORT_Pin_0 | PORT_Pin_1 | PORT_Pin_2 | PORT_Pin_3  | PORT_Pin_4  | PORT_Pin_5 | PORT_Pin_6 | PORT_Pin_7)
    #define BRD_EBC_DATA_PORT_LO8_FUNC    PORT_FUNC_MAIN

    //  Data: [PA0 .. PA15] = [D0 .. D15]    
    #define BRD_EBC_DATA_PORT_LO16        MDR_PORTA
    #define BRD_EBC_DATA_PORT_LO16_CLK    RST_CLK_PCLK_PORTA
    #define BRD_EBC_DATA_PORT_LO16_PINS   PORT_Pin_All
    #define BRD_EBC_DATA_PORT_LO16_FUNC   PORT_FUNC_MAIN

    //  Data: [PB0 .. PB15] = [D16 .. D31]
    #define BRD_EBC_DATA_PORT_HI16        MDR_PORTB
    #define BRD_EBC_DATA_PORT_HI16_CLK    RST_CLK_PCLK_PORTB
    #define BRD_EBC_DATA_PORT_HI16_PINS   PORT_Pin_All
    #define BRD_EBC_DATA_PORT_HI16_FUNC   PORT_FUNC_MAIN   
  
    //  Ctrl: PC0 - nWR, PC1 - nRD, //PC2 - ALE
    #define BRD_EBC_PORT_CTRL             MDR_PORTC
    #define BRD_EBC_PORT_CTRL_CLK         RST_CLK_PCLK_PORTC
    #define BRD_EBC_PORT_CTRL_PINS        (PORT_Pin_0 | PORT_Pin_1) //| PORT_Pin_2
    #define BRD_EBC_PORT_CTRL_FUNC        PORT_FUNC_MAIN

    //  Ctrl1: [PC9 .. PC12] = [BE0 .. BE3]
    #define BRD_EBC_PORT_CTRL_1_USED
    #define BRD_EBC_PORT_CTRL_1            MDR_PORTC
    #define BRD_EBC_PORT_CTRL_1_CLK        RST_CLK_PCLK_PORTC
    #define BRD_EBC_PORT_CTRL_1_PINS       (PORT_Pin_9 | PORT_Pin_10 | PORT_Pin_11 | PORT_Pin_12)
    #define BRD_EBC_PORT_CTRL_1_FUNC       PORT_FUNC_ALTER

    //  Addr: [PF3 .. PF15] = [A0 - A12]    
    #define BRD_EBC_PORT_ADDR20           MDR_PORTF
    #define BRD_EBC_PORT_ADDR20_CLK       RST_CLK_PCLK_PORTF
    #define BRD_EBC_PORT_ADDR20_PINS      (PORT_Pin_3  | PORT_Pin_4  | PORT_Pin_5  | PORT_Pin_6  | PORT_Pin_7  | PORT_Pin_8 | PORT_Pin_9 | \
                                           PORT_Pin_10 | PORT_Pin_11 | PORT_Pin_12 | PORT_Pin_13 | PORT_Pin_14 | PORT_Pin_15)
    #define BRD_EBC_PORT_ADDR20_FUNC      PORT_FUNC_ALTER

    //  Addr: [PD15] = [A13]
    #define BRD_EBC_PORT_ADDR20_1_USED
    #define BRD_EBC_PORT_ADDR20_1         MDR_PORTD
    #define BRD_EBC_PORT_ADDR20_1_CLK     RST_CLK_PCLK_PORTD
    #define BRD_EBC_PORT_ADDR20_1_PINS    PORT_Pin_15
    #define BRD_EBC_PORT_ADDR20_1_FUNC    PORT_FUNC_ALTER
  
    //  Addr: [PE0 .. PE5] = [A14 - A19]
    #define BRD_EBC_PORT_ADDR20_2_USED
    #define BRD_EBC_PORT_ADDR20_2         MDR_PORTE
    #define BRD_EBC_PORT_ADDR20_2_CLK     RST_CLK_PCLK_PORTE
    #define BRD_EBC_PORT_ADDR20_2_PINS    (PORT_Pin_0 | PORT_Pin_1 | PORT_Pin_2 | PORT_Pin_3  | PORT_Pin_4  | PORT_Pin_5 )
    #define BRD_EBC_PORT_ADDR20_2_FUNC    PORT_FUNC_ALTER    
    
    //  CtrlReady: [PF0] = [Ready]
    #define BRD_EBC_PORT_READY            MDR_PORTF
    #define BRD_EBC_PORT_READY_CLK        RST_CLK_PCLK_PORTF
    #define BRD_EBC_PORT_READY_PINS       PORT_Pin_0
    #define BRD_EBC_PORT_READY_FUNC       PORT_FUNC_ALTER    

    
    //  EBC SUMMARY
    #define BRD_EBS_A20_D32_CLK  (BRD_EBC_PORT_ADDR20_CLK | BRD_EBC_PORT_ADDR20_1_CLK | BRD_EBC_PORT_ADDR20_2_CLK | \
                                  BRD_EBC_DATA_PORT_LO16_CLK | BRD_EBC_DATA_PORT_HI16_CLK | \
                                  BRD_EBC_PORT_CTRL_CLK | BRD_EBC_PORT_CTRL_1_CLK)
                                  
//  ----------    LCD Definition -------------
    #define BRD_LCD_E1_PORT     MDR_PORTE
    #define BRD_LCD_E1_PIN      PORT_Pin_13

    #define BRD_LCD_E2_PORT     MDR_PORTE
    #define BRD_LCD_E2_PIN      PORT_Pin_14

    #define BRD_LCD_A0_PORT     MDR_PORTE
    #define BRD_LCD_A0_PIN      PORT_Pin_12

//    #define BRD_LCD_RES_PORT    MDR_PORTE
//    #define BRD_LCD_RES_PIN     PORT_Pin_10

    #define BRD_LCD_RW_PORT     MDR_PORTC
    #define BRD_LCD_RW_PIN      PORT_Pin_0

    #define BRD_LCD_E_PORT      MDR_PORTC
    #define BRD_LCD_E_PIN       PORT_Pin_2

    // Initialization
    #define BRD_LCD_CLOCK     (RST_CLK_PCLK_PORTA | RST_CLK_PCLK_PORTC | RST_CLK_PCLK_PORTE)

    #define BRD_LCD_IN_PORT         MDR_PORTA
    #define BRD_LCD_IN_PINS        (PORT_Pin_0 | PORT_Pin_1 | PORT_Pin_2 | PORT_Pin_3 | PORT_Pin_4 | PORT_Pin_5| PORT_Pin_6| PORT_Pin_7) 

    #define BRD_LCD_OUT_PORT        MDR_PORTE
    #define BRD_LCD_OUT_PINS       (PORT_Pin_12 | PORT_Pin_13 | PORT_Pin_14) 

    #define BRD_LCD_OUT_PORT_EX1    MDR_PORTC
    #define BRD_LCD_OUT_PINS_EX1   (PORT_Pin_0 | PORT_Pin_2)
    
    //  Commands
    #define LCD_CODE_BUS_OUT        MDR_PORTA->OE |= 0x00FF;
    
    #define LCD_CODE_BUS_IN         MDR_PORTA->OE &= 0xFF00;
                                
    #define LCD_CODE_WRITE(value)   MDR_PORTA->RXTX &= 0xFF00;          \
                                    MDR_PORTA->RXTX |= (value & 0xFF);
                                    
    #define LCD_CODE_READ     (uint8_t)(MDR_PORTA->RXTX & 0xFF);

//  ----------    DAC Definition -------------
    #define BRD_DAC1_CLOCK    RST_CLK_PCLK_PORTE
    #define BRD_DAC1_PORT     MDR_PORTE
    #define BRD_DAC1_PIN      PORT_Pin_1
    
    #define BRD_DAC2_CLOCK    RST_CLK_PCLK_PORTE
    #define BRD_DAC2_PORT     MDR_PORTE
    #define BRD_DAC2_PIN      PORT_Pin_2


#else
   Please, select board in brdSelect.h!

#endif    

#endif // _BRD_DEF_VE1
