#ifndef BRD_DEF_VE8_H
#define BRD_DEF_VE8_H

#ifdef USE_BOARD_VE_8 

//  UNLOCK KEY
    #define _KEY_ 				         0x8555AAA1

//  --------------  Buttons Definition  ------------
    #define BRD_BTN_PORT_KEY1     PORTE
    #define BRD_BTN_PIN_KEY1      PORT_Pin_18

    #define BRD_BTN_PORT_KEY2     PORTE
    #define BRD_BTN_PIN_KEY2      PORT_Pin_21
	
    #define BRD_BTN_PORT_KEY3     PORTE
    #define BRD_BTN_PIN_KEY3      PORT_Pin_22
	
    // for Initialization
    #define BRD_BTNs_PORT_CLK      CLKCTRL_PER0_CLK_MDR_PORTE_EN
    #define BRD_BTNs_PORT          PORTE
    #define BRD_BTNs_PIN_MASK      (BRD_BTN_PIN_KEY1 | BRD_BTN_PIN_KEY2 | BRD_BTN_PIN_KEY3)
    
    //  for Is_BtnAct_...
    #define BRD_BTNs_PUSH_TO_GND  // use if connected to power!

    #define BRD_BTN_PORT_SEL    BRD_BTN_PORT_KEY1
    #define BRD_BTN_PORT_UP     BRD_BTN_PORT_KEY2
    #define BRD_BTN_PORT_DOWN   BRD_BTN_PORT_KEY3

    #define BRD_BTN_PIN_SEL     BRD_BTN_PIN_KEY1
    #define BRD_BTN_PIN_UP      BRD_BTN_PIN_KEY2
    #define BRD_BTN_PIN_DOWN    BRD_BTN_PIN_KEY3


//  ----------    LEDs Definition -------------
    #define BRD_LED_PORT_CLK       CLKCTRL_PER0_CLK_MDR_PORTC_EN
    #define BRD_LED_PORT           PORTC
  
    #define BRD_LED_1              PORT_Pin_16
    #define BRD_LED_2              PORT_Pin_17
    #define BRD_LED_3              PORT_Pin_18
    #define BRD_LED_4              PORT_Pin_19	
    #define BRD_LED_5              PORT_Pin_20	
    #define BRD_LED_6              PORT_Pin_21	
    #define BRD_LED_7              PORT_Pin_22	
    #define BRD_LED_8              PORT_Pin_23	
  
    #define BRD_LED_Pins        (BRD_LED_1 | BRD_LED_2 | BRD_LED_3 | BRD_LED_4  \
                               | BRD_LED_5 | BRD_LED_6 | BRD_LED_7 | BRD_LED_8)

//  ----------    DMA Definition -------------
    #define BRD_DMA_CLOCK_SELECT  (CLKCTRL_PER0_CLK_MDR_DMA0_EN)

#else
   Please, select board in brdSelect.h!

#endif // USE_MDR1986VE3


#endif  // BRD_DEF_VE8_H
