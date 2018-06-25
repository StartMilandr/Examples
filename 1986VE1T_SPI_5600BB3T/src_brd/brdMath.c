#include <math.h>
#include "brdMath.h"


#define PI 3.1415926535

void FillSin(uint16_t count, uint16_t *pBuff, uint16_t amp, uint16_t bias)
{
  float    omega;  // Период сигнала
  uint16_t i;

  // Разделение периода сигнала на величину буфера
  omega = 2 * PI / count; 

  // Цикл формирования сигнала
  for (i = 0; i < count; i++)
    pBuff[i] = bias + amp * sin(omega * i);
}

void FillSaw(uint16_t count, uint16_t *pBuff, uint16_t amp, uint16_t bias)
{
  float    k;
  uint16_t i;

  // Разделение амплитуды сигнала на величину буфера
  k = (float) amp / count; 

  // Цикл формирования сигнала
  for (i = 0; i < count; i++)
     pBuff[i] = bias + k * i;
}

void FillTriangle(uint16_t count, uint16_t *pBuff, uint16_t amp, uint16_t bias)
{
  float    k;
  uint16_t i;
  uint16_t partCnt;

  // Rize
  partCnt = count / 2;
  k = (float) amp / partCnt;   
  for (i = 0; i < partCnt; i++)
     pBuff[i] = bias + k * i;
  
  //  Fall
  count = count - partCnt;
  k = (float) amp / count;   
  for (i = 0; i < count; i++)
     pBuff[partCnt + i] = bias + amp - k * i; 
}

void FillMeandr(uint16_t count, uint16_t *pBuff, uint16_t amp, uint16_t bias, float ratio)
{
	uint16_t minVal = bias; 
	uint16_t maxVal	= bias + amp;
	
	uint16_t fallCnt = (count * ratio);
  uint16_t i;

  // Цикл формирования сигнала		
  for (i = 0; i < count; i++)
	  if (i < fallCnt)
      pBuff[i] = minVal;
		else
		  pBuff[i] = maxVal;
}
