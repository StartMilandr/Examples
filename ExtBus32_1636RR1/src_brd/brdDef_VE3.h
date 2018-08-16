#ifndef _BRD_DEF_VE3
#define _BRD_DEF_VE3

#ifdef USE_BOARD_VE_3

//  Buttons Definition
    #define BRD_BTN_PORT_SEL       MDR_PORTG 
    #define BRD_BTN_PIN_SEL        PORT_Pin_14  //sw10  

    #define BRD_BTN_PORT_UP        MDR_PORTG
    #define BRD_BTN_PIN_UP         PORT_Pin_12  // sw8  
	
    #define BRD_BTN_PORT_RIGHT     MDR_PORTG    
    #define BRD_BTN_PIN_RIGHT      PORT_Pin_11  // sw7 
	
    #define BRD_BTN_PORT_DOWN      MDR_PORTG   
    #define BRD_BTN_PIN_DOWN       PORT_Pin_15	// sw11 
	
    #define BRD_BTN_PORT_LEFT      MDR_PORTG  
    #define BRD_BTN_PIN_LEFT       PORT_Pin_7   // sw6
	
    #define BRD_BTN_PORT_BACK      MDR_PORTG  
    #define BRD_BTN_PIN_BACK       PORT_Pin_13  // sw9

    // for Initialization
    #define BRD_BTNs_PORT_CLK      RST_CLK_PCLK2_PORTG
    #define BRD_BTNs_PORT_MASK     MDR_PORTG
    #define BRD_BTNs_PIN_MASK      (BRD_BTN_PIN_SEL | BRD_BTN_PIN_UP | BRD_BTN_PIN_RIGHT | BRD_BTN_PIN_DOWN | BRD_BTN_PIN_LEFT | BRD_BTN_PIN_BACK)
    
    //  for Is_BtnAct_...
    //#define BRD_BTNs_DO_INV  connected to power!

//  LEDs Definition
    #define BRD_LED_PORT_CLK       RST_CLK_PCLK_PORTB
    #define BRD_LED_PORT           MDR_PORTB
  
    #define BRD_LED_1              PORT_Pin_0
    #define BRD_LED_2              PORT_Pin_1
    #define BRD_LED_3              PORT_Pin_2
    #define BRD_LED_4              PORT_Pin_3	
    #define BRD_LED_5              PORT_Pin_4	
    #define BRD_LED_6              PORT_Pin_5	
    #define BRD_LED_7              PORT_Pin_6	
    #define BRD_LED_8              PORT_Pin_7	
  
    #define BRD_LED_Pins        (BRD_LED_1 | BRD_LED_2 | BRD_LED_3 | BRD_LED_4  \
                               | BRD_LED_5 | BRD_LED_6 | BRD_LED_7 | BRD_LED_8)

#else
   Please, select board in brdSelect.h!

#endif // USE_MDR1986VE3

#endif // _BRD_DEF_VE3
