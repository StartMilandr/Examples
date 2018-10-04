#ifndef _BRD_DMA_SELECT_H
#define _BRD_DMA_SELECT_H

#include "brdDMA.h"

// ��������� ���������� ������� DMA
DMA_CtrlDataInitTypeDef DMA_DataCtrl_Pri = 
{
  0,                            // DMA_SourceBaseAddr - ����� ��������� ������
  0,                            // DMA_DestBaseAddr   - ����� ���������� ������
  DMA_SourceIncWord,            // DMA_SourceIncSize  - �������������� ������ ��������� ������
  DMA_DestIncNo,                // DMA_DestIncSize    - �������������� ������ ���������� ������
  DMA_MemoryDataSize_Word,      // DMA_MemoryDataSize - ������ ������ ������
  DMA_Mode_Basic,               // DMA_Mode           - ����� ������ DMA
  10,                           // DMA_CycleSize      - ���. ������ �� �������� (����� ����� DMA)
  DMA_Transfers_1,              // DMA_NumContinuous  - ���������� ����������� ������� (�� ���������)
  DMA_SourcePrivileged,         // DMA_SourceProtCtrl - ����� ������ �����������
  DMA_DestPrivileged            // DMA_DestProtCtrl   - ����� ������ ���������
};
  
//  ��������� ������ DMA
DMA_ChannelInitTypeDef DMA_ChanCtrl = 
{
  &DMA_DataCtrl_Pri,        // DMA_PriCtrlData         - �������� ��������� ���������� �������
  &DMA_DataCtrl_Pri,        // DMA_AltCtrlStr          - �������������� ��������� ���������� �������
   0, //DMA_AHB_Privileged,      // DMA_ProtCtrl 
   DMA_Priority_Default,    // DMA_Priority            - ��������� ������
   DMA_BurstClear,          // DMA_UseBurst
   DMA_CTRL_DATA_PRIMARY    // DMA_SelectDataStructure - ������������ ��������� ���������� �������
};
  
#endif	// _BRD_DMA_SELECT_H


