#ifndef _BRD_UTILS_H
#define _BRD_UTILS_H

#include <stdint.h>

#define HWREG(x) (*((volatile uint32_t *)(x)))

void Delay(uint32_t ticks);

//  Value Compare
typedef uint32_t (*BRD_CompareFunc)(uint32_t value, uint32_t level);

uint32_t BRD_IsGT(uint32_t value, uint32_t level);
uint32_t BRD_IsLT(uint32_t value, uint32_t level);

uint32_t BRD_IsEQ(uint32_t value, uint32_t level);
uint32_t BRD_IsNE(uint32_t value, uint32_t level);


#endif //_BRD_UTILS_H
