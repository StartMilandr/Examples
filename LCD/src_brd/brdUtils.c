#include "brdUtils.h"

void Delay(uint32_t ticks)
{
	uint32_t i;
	for(i = 0; i < ticks; i++){}
}

uint32_t BRD_IsGT(uint32_t value, uint32_t level)
{
  return value > level;
}

uint32_t BRD_IsLT(uint32_t value, uint32_t level)
{
  return value < level;
}

uint32_t BRD_IsEQ(uint32_t value, uint32_t level)
{
  return value == level;
}

uint32_t BRD_IsNE(uint32_t value, uint32_t level)
{
  return value != level;
}


