#ifndef _BRD_FLASH_EXTBUS_H
#define _BRD_FLASH_EXTBUS_H

#include <stdint.h>


typedef enum {flashOk, flashFault} FlashStatus;

FlashStatus EraseFullFLASH(void);
FlashStatus EraseFLASHSector(uint32_t SectorInd);

FlashStatus WriteFLASH(uint32_t ADR, uint32_t DATA);
uint32_t ReadFLASH(uint32_t ADR);

void FlashBypassReset(void);
void FlashReset(void);

void BRD_ExtBus_Init_1636RR1_nCE (void);

#endif  // _BRD_FLASH_EXTBUS_H

