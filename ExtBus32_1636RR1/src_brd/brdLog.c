#include "brdLog.h"

#define LOG_BUFF_Len  200

uint32_t _TestVar[10];

uint16_t LogData1[LOG_BUFF_Len];

BRD_LogRec BRD_LogRec1 =
{
  LogData1,
  LOG_BUFF_Len,
  0,
  0  
};

void BRD_LOG_Clear(BRD_LogRec *pLogRec)
{
  uint16_t i;
  
  for (i = 0; i < pLogRec->BuffLen; ++i)
    pLogRec->pBuff[i] = 0;
  pLogRec->IndWR = 0;
  pLogRec->DataCnt = 0;
}

void BRD_LOG_Add(BRD_LogRec *pLogRec, uint16_t value)
{
  pLogRec->pBuff[pLogRec->IndWR++] = value;
  pLogRec->DataCnt++;
  if (pLogRec->IndWR >= pLogRec->BuffLen)
    pLogRec->IndWR = 0;
}
