#ifndef _BRD_DEF_VE91
#define _BRD_DEF_VE91

#ifdef USE_BOARD_VE_91

#include "brdDef_VE9x.h"

//  --------------  Buttons Definition  ------------
    #define BRD_BTN_PORT_SEL       MDR_PORTC
    #define BRD_BTN_PIN_SEL        PORT_Pin_10

    #define BRD_BTN_PORT_UP        MDR_PORTC
    #define BRD_BTN_PIN_UP         PORT_Pin_11
	
    #define BRD_BTN_PORT_RIGHT     MDR_PORTC
    #define BRD_BTN_PIN_RIGHT      PORT_Pin_14
	
    #define BRD_BTN_PORT_DOWN      MDR_PORTC
    #define BRD_BTN_PIN_DOWN       PORT_Pin_12
	
    #define BRD_BTN_PORT_LEFT      MDR_PORTC
    #define BRD_BTN_PIN_LEFT       PORT_Pin_13

    // for Initialization
    #define BRD_BTNs_PORT_CLK      RST_CLK_PCLK_PORTC
    #define BRD_BTNs_PORT_MASK     MDR_PORTC
    #define BRD_BTNs_PIN_MASK      BRD_BTN_PIN_SEL | BRD_BTN_PIN_UP | BRD_BTN_PIN_RIGHT | BRD_BTN_PIN_DOWN | BRD_BTN_PIN_LEFT

    //  for Is_BtnAct_...
    #define BRD_BTNs_PUSH_TO_GND 

//  ----------    LEDs Definition -------------
    #define BRD_LED_1 	           PORT_Pin_10
    #define BRD_LED_2 	           PORT_Pin_11
    #define BRD_LED_3 	           PORT_Pin_12
    #define BRD_LED_4 	           PORT_Pin_13

    #define BRD_LED_PORT_CLK       RST_CLK_PCLK_PORTD
    #define BRD_LED_PORT           MDR_PORTD    
    #define BRD_LED_Pins           BRD_LED_1 | BRD_LED_2 | BRD_LED_3 | BRD_LED_4
    
    #define BRD_LED_JTAG_PROT_CLR  (0xFFFFFFE0)   


//  ----------  LCD Definition ---------------
    #define BRD_LCD_E1_PORT     MDR_PORTE
    #define BRD_LCD_E1_PIN      PORT_Pin_4

    #define BRD_LCD_E2_PORT     MDR_PORTE
    #define BRD_LCD_E2_PIN      PORT_Pin_5

    #define BRD_LCD_RES_PORT    MDR_PORTE
    #define BRD_LCD_RES_PIN     PORT_Pin_10

    #define BRD_LCD_RW_PORT     MDR_PORTC
    #define BRD_LCD_RW_PIN      PORT_Pin_2

    #define BRD_LCD_A0_PORT     MDR_PORTE
    #define BRD_LCD_A0_PIN      PORT_Pin_11

    #define BRD_LCD_E_PORT      MDR_PORTC
    #define BRD_LCD_E_PIN       PORT_Pin_7

    // Initialization
    #define BRD_LCD_CLOCK     (RST_CLK_PCLK_PORTA | RST_CLK_PCLK_PORTC | RST_CLK_PCLK_PORTE)

    #define BRD_LCD_IN_PORT         MDR_PORTA
    #define BRD_LCD_IN_PINS        (PORT_Pin_0 | PORT_Pin_1 | PORT_Pin_2 | PORT_Pin_3 | PORT_Pin_4 | PORT_Pin_5| PORT_Pin_6| PORT_Pin_7) 

    #define BRD_LCD_OUT_PORT        MDR_PORTE
    #define BRD_LCD_OUT_PINS       (PORT_Pin_4 | PORT_Pin_5 | PORT_Pin_10 | PORT_Pin_11) 

    #define BRD_LCD_OUT_PORT_EX1    MDR_PORTC
    #define BRD_LCD_OUT_PINS_EX1   (PORT_Pin_2 | PORT_Pin_7)
    
    //  Commands
    #define LCD_CODE_BUS_OUT        MDR_PORTA->OE |= 0x00FF;
    
    #define LCD_CODE_BUS_IN         MDR_PORTA->OE &= 0xFF00;
                                
    #define LCD_CODE_WRITE(value)   MDR_PORTA->RXTX &= 0xFF00;          \
                                    MDR_PORTA->RXTX |= (value & 0xFF);
                                    
    #define LCD_CODE_READ     (uint8_t)(MDR_PORTA->RXTX & 0xFF);

#else
   Please, select board in brdSelect.h!

#endif 

#endif // _BRD_DEF_VE91
