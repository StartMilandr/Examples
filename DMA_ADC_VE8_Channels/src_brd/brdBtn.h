#ifndef _BRD_BTN_H
#define _BRD_BTN_H

#include "brdDef.h"

#ifdef USE_BOARD_VE_8 
  #include  <mdr32f8_port.h>
  #include  <mdr32f8_clkctrl.h>

#else  
  #include <MDR32F9Qx_port.h>
  #include <MDR32F9Qx_rst_clk.h>
#endif

void BRD_BTNs_Init (void);

uint32_t BRD_Is_BntAct_Select(void);
uint32_t BRD_Is_BntAct_Up    (void);
uint32_t BRD_Is_BntAct_Down  (void);
uint32_t BRD_Is_BntAct_Left  (void);
uint32_t BRD_Is_BntAct_Right (void);

uint32_t BRD_Is_BntAct_Back (void);


#endif	// _BRD_BTN_H
