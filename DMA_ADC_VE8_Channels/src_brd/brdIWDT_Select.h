#ifndef BRD_IWDT_SELECT_H
#define BRD_IWDT_SELECT_H

#include "brdIWDT.h"

BrdIWDT_Obj brdIWDT_2sec = {
  
  IWDG_Prescaler_128,               //  Prescaler;
	(2 * LSI_Value / 128)               //  ReloadPeriod
};


#endif  //BRD_IWDT_SELECT_H
