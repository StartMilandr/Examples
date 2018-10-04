#ifndef _BRD_DMA_SELECT_H
#define _BRD_DMA_SELECT_H

#include "brdDMA.h"

// Настройки управления данными DMA
DMA_CtrlDataInitTypeDef DMA_DataCtrl_Pri = 
{
  0,                            // DMA_SourceBaseAddr - Адрес источника данных
  0,                            // DMA_DestBaseAddr   - Адрес назначения данных
  DMA_SourceIncWord,            //DMA_SourceIncNo,              // DMA_SourceIncSize  - Автоувеличение адреса источника данных
  DMA_DestIncWord,              // DMA_DestIncSize    - Автоувеличение адреса назначения данных
  DMA_MemoryDataSize_Word,      // DMA_MemoryDataSize - Размер пакета данных
  DMA_Mode_Basic,               // DMA_Mode           - Режим работы DMA
  1,                            // DMA_CycleSize      - Кол. данных на передачу (длина цикла DMA)
  DMA_Transfers_1,              // DMA_NumContinuous  - Количество непрерывных передач (до арбитража)
  DMA_SourcePrivileged,         // DMA_SourceProtCtrl - Режим защиты передатчика
  DMA_DestPrivileged            // DMA_DestProtCtrl   - Режим защиты приемника
};
  
//  Настройки канала DMA
DMA_ChannelInitTypeDef DMA_ChanCtrl = 
{
  &DMA_DataCtrl_Pri,        // DMA_PriCtrlData         - Основная структура управления данными
  &DMA_DataCtrl_Pri,        // DMA_AltCtrlStr          - Альтернативная структура управления данными
   DMA_AHB_Privileged, //0, //DMA_AHB_Privileged,      // DMA_ProtCtrl 
   DMA_Priority_High, //DMA_Priority_Default,    // DMA_Priority            - Приоритет канала
   DMA_BurstClear,          // DMA_UseBurst
   DMA_CTRL_DATA_PRIMARY    // DMA_SelectDataStructure - Используемая структура управления данными
};
  
#endif	// _BRD_DMA_SELECT_H


