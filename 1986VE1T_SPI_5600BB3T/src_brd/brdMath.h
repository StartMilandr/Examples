#ifndef _BRD_MATH_H
#define _BRD_MATH_H

#include <StdInt.h>

void FillSin(uint16_t count, uint16_t *pBuff, uint16_t amp, uint16_t bias);
void FillSaw(uint16_t count, uint16_t *pBuff, uint16_t amp, uint16_t bias);
void FillTriangle(uint16_t count, uint16_t *pBuff, uint16_t amp, uint16_t bias);
void FillMeandr(uint16_t count, uint16_t *pBuff, uint16_t amp, uint16_t bias, float ratio);


#endif //_BRD_MATH_H
