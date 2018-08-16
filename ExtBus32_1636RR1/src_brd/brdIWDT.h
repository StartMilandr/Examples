#ifndef BRD_IWDT_H
#define BRD_IWDT_H

#include "MDR32F9Qx_config.h"
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_iwdg.h"

typedef struct {
  uint32_t Prescaler;
  uint32_t ReloadPeriod;
} BrdIWDT_Obj;

void BRD_IWDT_Init(BrdIWDT_Obj *Obj);

#endif  //BRD_IWDT_H
