#ifndef _BRD_DEF_VE93
#define _BRD_DEF_VE93


#ifdef USE_BOARD_VE_93

#include "brdDef_VE9x.h"

//  --------------  Buttons Definition  ------------
    #define BRD_BTN_PORT_SEL       MDR_PORTC
    #define BRD_BTN_PIN_SEL        PORT_Pin_0

    #define BRD_BTN_PORT_UP        MDR_PORTD
    #define BRD_BTN_PIN_UP         PORT_Pin_0
	
    #define BRD_BTN_PORT_RIGHT     MDR_PORTE
    #define BRD_BTN_PIN_RIGHT      PORT_Pin_6
	
    #define BRD_BTN_PORT_DOWN      MDR_PORTD
    #define BRD_BTN_PIN_DOWN       PORT_Pin_1
	
    #define BRD_BTN_PORT_LEFT      MDR_PORTE
    #define BRD_BTN_PIN_LEFT       PORT_Pin_3
	
    // for Initialization
    #define BRD_BTNs_PORT_CLK          RST_CLK_PCLK_PORTC | RST_CLK_PCLK_PORTD | RST_CLK_PCLK_PORTE

    #define BRD_BTNs_PORT_MASK         MDR_PORTC
    #define BRD_BTNs_PIN_MASK          PORT_Pin_0

    #define BRD_BTNS_DO_INIT_ext1
    #define BRD_BTNs_PORT_MASK_ext1    MDR_PORTD
    #define BRD_BTNs_PIN_MASK_ext1     PORT_Pin_0 | PORT_Pin_1

    #define BRD_BTNS_DO_INIT_ext2
    #define BRD_BTNs_PORT_MASK_ext2    MDR_PORTE
    #define BRD_BTNs_PIN_MASK_ext2     PORT_Pin_3 | PORT_Pin_6
    
    //  for Is_BtnAct_...
    #define BRD_BTNs_PUSH_TO_GND    

//  ----------    LEDs Definition -------------
    #define BRD_LED_1 	           PORT_Pin_0
    #define BRD_LED_2 	           PORT_Pin_1

    #define BRD_LED_PORT_CLK       RST_CLK_PCLK_PORTF
    #define BRD_LED_PORT           MDR_PORTF    
    #define BRD_LED_Pins           BRD_LED_1 | BRD_LED_2


//  ----------  LCD Definition ---------------
//  conflicts with LEDs!
    #define BRD_LCD_E1_PORT     MDR_PORTF
    #define BRD_LCD_E1_PIN      PORT_Pin_0

    #define BRD_LCD_E2_PORT     MDR_PORTF
    #define BRD_LCD_E2_PIN      PORT_Pin_1

    #define BRD_LCD_RES_PORT    MDR_PORTF
    #define BRD_LCD_RES_PIN     PORT_Pin_2

    #define BRD_LCD_RW_PORT     MDR_PORTF
    #define BRD_LCD_RW_PIN      PORT_Pin_3

    #define BRD_LCD_A0_PORT     MDR_PORTF
    #define BRD_LCD_A0_PIN      PORT_Pin_4

    #define BRD_LCD_E_PORT      MDR_PORTD
    #define BRD_LCD_E_PIN       PORT_Pin_3

    // Initialization
    #define BRD_LCD_CLOCK           (RST_CLK_PCLK_PORTA | RST_CLK_PCLK_PORTF | RST_CLK_PCLK_PORTD)
                                    // D0 .. D7
    #define BRD_LCD_IN_PORT         MDR_PORTA
    #define BRD_LCD_IN_PINS        (PORT_Pin_0 | PORT_Pin_1 | PORT_Pin_2 | PORT_Pin_3 | PORT_Pin_4 | PORT_Pin_5 | PORT_Pin_6 | PORT_Pin_7) 
                                    //  E1, E2, RES, RW, A0
    #define BRD_LCD_OUT_PORT        MDR_PORTF
    #define BRD_LCD_OUT_PINS       (PORT_Pin_0 | PORT_Pin_1 | PORT_Pin_2 | PORT_Pin_3 | PORT_Pin_4) 
                                    //  E
    #define BRD_LCD_OUT_PORT_EX1    MDR_PORTD
    #define BRD_LCD_OUT_PINS_EX1   (PORT_Pin_3)
    
    //  Commands
    #define LCD_CODE_BUS_OUT        MDR_PORTA->OE |= 0x00FF;
    
    #define LCD_CODE_BUS_IN         MDR_PORTA->OE &= 0xFF00;
                                
    #define LCD_CODE_WRITE(value)   MDR_PORTA->RXTX &= 0xFF00;          \
                                    MDR_PORTA->RXTX |= (value & 0xFF);
                                    
    #define LCD_CODE_READ           (uint8_t)(MDR_PORTA->RXTX & 0xFF);

#else
   Please, select board in brdSelect.h!

#endif 

#endif // _BRD_DEF_VE93
