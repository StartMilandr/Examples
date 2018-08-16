#ifndef BRD_LOG_H
#define BRD_LOG_H

#include <stdint.h>

typedef struct
{
  uint16_t *pBuff;
  uint16_t BuffLen;
  uint16_t IndWR;
  uint16_t DataCnt;
  
} BRD_LogRec;


void BRD_LOG_Clear(BRD_LogRec *pLogRec);
void BRD_LOG_Add(BRD_LogRec *pLogRec, uint16_t value);

extern BRD_LogRec BRD_LogRec1;

extern uint32_t _TestVar[10];

enum {ubs_NewSend, usb_SendOk, usb_SendFault, usb_SendReady, usb_ReceiveSend, usb_ReceiveExit,
      usb_IN_SendPart, usb_IN_SendFinish, usb_IN_Err, usb_IN_CallHandler, usb_IN_Idle, usb_IN_ErrSend,
      usb_Out_Read, usb_Out_Call_Handler, usb_Out_Idle,
      usb_IN_PntInit,
};

#endif

