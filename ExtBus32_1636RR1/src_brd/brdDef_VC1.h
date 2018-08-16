#ifndef _BRD_DEF_VC1
#define _BRD_DEF_VC1

#ifdef USE_BOARD_VC1


//  --------------  Buttons Definition  ------------
    #define BRD_BTN_PORT_SEL       MDR_PORTC    // PC0
    #define BRD_BTN_PIN_SEL        PORT_Pin_0

    #define BRD_BTN_PORT_UP        MDR_PORTC    // PC3
    #define BRD_BTN_PIN_UP         PORT_Pin_3
	
    #define BRD_BTN_PORT_RIGHT     MDR_PORTC    // PC6
    #define BRD_BTN_PIN_RIGHT      PORT_Pin_6
	
    #define BRD_BTN_PORT_DOWN      MDR_PORTC    // PC4
    #define BRD_BTN_PIN_DOWN       PORT_Pin_4
	
    #define BRD_BTN_PORT_LEFT      MDR_PORTC    // PC5
    #define BRD_BTN_PIN_LEFT       PORT_Pin_5
	
    // for Initialization
    #define BRD_BTNs_PORT_CLK          RST_CLK_PCLK_PORTC

    #define BRD_BTNs_PORT_MASK         MDR_PORTC
    #define BRD_BTNs_PIN_MASK          BRD_BTN_PIN_SEL | BRD_BTN_PIN_UP | BRD_BTN_PIN_RIGHT | BRD_BTN_PIN_DOWN | BRD_BTN_PIN_LEFT
    
    //  for Is_BtnAct_...
    #define BRD_BTNs_PUSH_TO_GND    

//  ----------    LEDs Definition -------------
    #define BRD_LED_1 	           PORT_Pin_15    // PB15 -  VD3
    #define BRD_LED_2 	           PORT_Pin_14    // PB14 -  VD4
    #define BRD_LED_3 	           PORT_Pin_13    // PB13 -  VD5
    #define BRD_LED_4 	           PORT_Pin_12    // PB12 -  VD6
    #define BRD_LED_5 	           PORT_Pin_11    // PB11 -  VD7

    #define BRD_LED_PORT_CLK       RST_CLK_PCLK_PORTB
    #define BRD_LED_PORT           MDR_PORTB
    #define BRD_LED_Pins           BRD_LED_1 | BRD_LED_2 | BRD_LED_3 | BRD_LED_4 | BRD_LED_5

//  ----------  LCD Definition ---------------
//    #define BRD_LCD_E1_PORT     MDR_PORTE     // PE4
//    #define BRD_LCD_E1_PIN      PORT_Pin_4

//    #define BRD_LCD_E2_PORT     MDR_PORTE     // PE5
//    #define BRD_LCD_E2_PIN      PORT_Pin_5

//    #define BRD_LCD_RES_PORT    MDR_PORTD     // PD9
//    #define BRD_LCD_RES_PIN     PORT_Pin_9

//    #define BRD_LCD_RW_PORT     MDR_PORTC     // PC2
//    #define BRD_LCD_RW_PIN      PORT_Pin_2

//    #define BRD_LCD_A0_PORT     MDR_PORTE     // PE11
//    #define BRD_LCD_A0_PIN      PORT_Pin_11

//    #define BRD_LCD_E_PORT      MDR_PORTC     // PC7
//    #define BRD_LCD_E_PIN       PORT_Pin_7

//    // Initialization
//    #define BRD_LCD_CLOCK     (RST_CLK_PCLK_PORTA | RST_CLK_PCLK_PORTB | RST_CLK_PCLK_PORTC | RST_CLK_PCLK_PORTF)

//    #define BRD_LCD_IN_PORT         MDR_PORTA
//    #define BRD_LCD_IN_PINS        (PORT_Pin_0 | PORT_Pin_1 | PORT_Pin_2 | PORT_Pin_3 | PORT_Pin_4 | PORT_Pin_5) 

//    #define BRD_LCD_IN_PORT_EX1     MDR_PORTF
//    #define BRD_LCD_IN_PINS_EX1    (PORT_Pin_2 | PORT_Pin_3)

//    #define BRD_LCD_OUT_PORT        MDR_PORTB
//    #define BRD_LCD_OUT_PINS       (PORT_Pin_7 | PORT_Pin_8 | PORT_Pin_9 | PORT_Pin_10) 

//    #define BRD_LCD_OUT_PORT_EX1    MDR_PORTC
//    #define BRD_LCD_OUT_PINS_EX1   (PORT_Pin_0 | PORT_Pin_1)
//    
//    //  Commands
//    #define LCD_CODE_BUS_OUT        MDR_PORTA->OE |= 0x003F; \
//                                    MDR_PORTF->OE |= 0x000C;
//    
//    #define LCD_CODE_BUS_IN         MDR_PORTA->OE &= 0xFFC0;  \
//                                    MDR_PORTF->OE &= 0xFFF3;
//                                
//    #define LCD_CODE_WRITE(value)   MDR_PORTA->RXTX &= 0xFFC0;          \
//                                    MDR_PORTA->RXTX |= (value & 0x3F);  \
//                                    MDR_PORTF->RXTX &= 0xFFF3;          \
//                                    MDR_PORTF->RXTX |= ((value >> 4) & 0x0C);
//                                    
//    #define LCD_CODE_READ     (uint8_t)(MDR_PORTA->RXTX & 0x3F) | (uint8_t)((MDR_PORTF->RXTX << 4) & 0xC0);


//  ----------  SDIO Definition ---------------
    #define BRD_SDIO_PIN_CLK      PORT_Pin_8       // PC8
    #define BRD_SDIO_PIN_CMD      PORT_Pin_1       // PC1
    #define BRD_SDIO_PIN_D0       PORT_Pin_10      // PC10
    #define BRD_SDIO_PIN_D1       PORT_Pin_11      // PC11
    #define BRD_SDIO_PIN_D2       PORT_Pin_12      // PC12
    #define BRD_SDIO_PIN_D3       PORT_Pin_13      // PC13

    #define BRD_SDIO_PORT_CLK       RST_CLK_PCLK_PORTC
    #define BRD_SDIO_PORT           MDR_PORTC
    
    #define BRD_SDIO_PORT_D0        MDR_PORTC //  for Write ack
    
    #define BRD_SDIO_INIT_PORT           MDR_PORTC
    #define BRD_SDIO_INIT_PIN            BRD_SDIO_PIN_D0 | BRD_SDIO_PIN_D1 | BRD_SDIO_PIN_D2 | BRD_SDIO_PIN_D3
    #define BRD_SDIO_INIT_FUNC           PORT_FUNC_MAIN
    #define BRD_SDIO_INIT_PULLUP         PORT_PULL_UP_ON

    #define BRD_SDIO_INIT_PORT_1         MDR_PORTC
    #define BRD_SDIO_INIT_PIN_1          BRD_SDIO_PIN_CMD
    #define BRD_SDIO_INIT_FUNC_1         PORT_FUNC_OVERRID
    #define BRD_SDIO_INIT_PULLUP_1       PORT_PULL_UP_ON
    
    #define BRD_SDIO_INIT_PORT_2         MDR_PORTC
    #define BRD_SDIO_INIT_PIN_2          BRD_SDIO_PIN_CLK
    #define BRD_SDIO_INIT_FUNC_2         PORT_FUNC_MAIN
    #define BRD_SDIO_INIT_PULLUP_2       PORT_PULL_UP_OFF    

#else
   Please, select board in brdSelect.h!

#endif 

#endif // _BRD_DEF_VC1

