#ifndef BRD_POWER_H
#define BRD_POWER_H

#include <stdint.h>

#include <MDR32F9Qx_port.h>
#include <MDR32F9Qx_rst_clk.h>
#include <MDR32F9Qx_power.h> 

typedef struct {
  uint32_t LevelPVD;
  uint32_t LevelPVDBat;
  uint32_t EventInvMask;    //  POWER_PVD_INV | POWER_PVBD_INV
  uint32_t IrqEnaMask;
} BRD_Power_Obj;

void BRD_PowerPVD_EnaIRQ(uint32_t IrqEnaMask, uint32_t enable);
void BRD_Power_Init(BRD_Power_Obj *powerCfg);
void BRD_Power_InverseEvent(uint32_t EventInvMask);

//  //  Struct example
//BRD_Power_Obj PowerCfg = {
//  .LevelPVD =     PWR_PVDlevel_2V0,
//  .LevelPVDBat =  PWR_PVDlevel_2V0,
//  .EventInvMask = POWER_PVD_INV | POWER_PVBD_INV,
//  .IrqEnaMask =   POWER_PVD_IT  | POWER_PVBD_IT
//} ;

#endif //BRD_POWER_H

