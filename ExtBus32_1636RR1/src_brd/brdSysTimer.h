#ifndef BRD_SYSTIMER_H
#define BRD_SYSTIMER_H

#include <stdint.h>
#include "brdDef.h"
#include <MDR32F9Qx_config.h>

void SysTickStart(uint32_t ticks);
void SysTickStop(void);

#endif //BRD_SYSTIMER_H

