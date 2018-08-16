#include "brdPort.h"

void BRD_Port_Init (brdPort_Obj* BRD_Port)
{
  // Port Clock
  RST_CLK_PCLKcmd (BRD_Port->Port_ClockMask, ENABLE);

  // PinsInit
  BRD_Port->pInitStruct->PORT_Pin   = BRD_Port->Port_PinsSel;
  BRD_Port->pInitStruct->PORT_FUNC  = BRD_Port->Port_PinsFunc;  
  
  PORT_Init (BRD_Port->PORTx, BRD_Port->pInitStruct);
} 
