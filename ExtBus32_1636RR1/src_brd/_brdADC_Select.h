#ifndef _BRD_ADC_SELECT__H
#define _BRD_ADC_SELECT__H

#include "brdDef.h"

#if defined (USE_BOARD_VE_91) || defined (USE_BOARD_VE_92) || defined (USE_BOARD_VE_93) || defined (USE_BOARD_VE_94)
  #define BRD_ADC_CH_PIN       BRD_ADC_7_PIN
  #define BRD_ADC_CH_PORT      BRD_ADC_7_PORT
  #define BRD_ADC_CH_CLOCK     BRD_ADC_7_CLOCK
#endif

#endif //_BRD_ADC_SELECT__H
