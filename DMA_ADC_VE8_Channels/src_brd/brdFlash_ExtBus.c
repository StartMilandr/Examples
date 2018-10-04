#include <MDR32F9Qx_port.h>

#include "brdFlash_ExtBus.h"
#include "brdUtils.h"
#include "brdDef.h"

//#define BRD_EXTBUS_START_ADDR	0x10000000  - Defined through brdDefs.h in brdDef_VExx.h
#define EXTBUS_ADDR(x) (BRD_EXTBUS_START_ADDR + ((x) << 2))
#define HWEXTBUS(x) HWREG(EXTBUS_ADDR(x))

#define WAIT_STARTED_CYCLES 100
#define TRY_START_COUNT			10

FlashStatus WaitStatusBit_D7(uint32_t ADR, uint32_t DATA);
FlashStatus WaitProgressBit_D6(uint32_t ADR);
uint32_t WaitStarted_D6(uint32_t ADR, uint32_t waitCycles);

uint32_t ReadFLASH(uint32_t ADR)
{
	return (HWEXTBUS(ADR));
}

void FlashBypassReset(void)
{
	HWEXTBUS(0x555) = 0x90909090;
	HWEXTBUS(0x2AA) = 0x00000000;
}	

void FlashReset(void)
{
	HWEXTBUS(0) = 0xf0f0f0f0;
}	

FlashStatus WriteFLASH(uint32_t ADR, uint32_t DATA)
{	
	FlashStatus result;	
	uint32_t i;

	result = flashFault;
	for (i = 0; i < TRY_START_COUNT; ++i)
	{
		//	Send commandt to start
		HWEXTBUS(0x555) = 0xAAAAAAAA;
		HWEXTBUS(0x2AA) = 0x55555555;
		HWEXTBUS(0x555) = 0xA0A0A0A0;
		//	Write Data
		HWEXTBUS(ADR) = DATA;

		if (WaitStarted_D6(ADR, WAIT_STARTED_CYCLES))
		{	
			result = flashOk;
			break;
		}	
		else
			FlashReset();
	}
	
	if (result == flashOk)
	{	
		result =  WaitStatusBit_D7(ADR, DATA);
		if (result != flashOk)
			FlashReset();	
	}

	return result;
}

FlashStatus EraseFullFLASH(void)
{
	volatile uint32_t status, status_last;
	FlashStatus result;
	uint32_t i;

	result = flashFault;
	for (i = 0; i < TRY_START_COUNT; ++i)
	{
		//	Send commandt to start
		HWEXTBUS(0x555) = 0xAAAAAAAA;
		HWEXTBUS(0x2AA) = 0x55555555;
		HWEXTBUS(0x555) = 0x80808080;
		HWEXTBUS(0x555) = 0xAAAAAAAA;
		HWEXTBUS(0x2AA) = 0x55555555;
		HWEXTBUS(0x555) = 0x10101010;

		if (WaitStarted_D6(0, WAIT_STARTED_CYCLES))
		{
			result = flashOk;			
			break;
		}	
		else
			FlashReset();
	}	
	
	if (result == flashOk)
	{	
		result = WaitProgressBit_D6(0);
		if (result != flashOk)
			FlashReset();
	}	
	
	return result;
}

uint32_t WaitStarted_D6(uint32_t ADR, uint32_t waitCycles)
{
	uint32_t i;
	volatile uint32_t status;
	volatile uint32_t status_last;	

	status_last = HWEXTBUS(ADR);
	
	for (i = 0; i < waitCycles; ++i)
	{
		status = HWEXTBUS(ADR);
		
		if (status != status_last)
			return 1;
		else
			status_last = status;
	}
	return 0;
}

FlashStatus WaitStatusBit_D7(uint32_t ADR, uint32_t DATA)
{
	volatile uint32_t status;
	volatile uint32_t status_last;
	volatile uint32_t D6_Stopped = 0;

	while (1)
	{
		// Status Update
		status = HWEXTBUS(ADR);
		//	Check completed - D7 bit
		if ((status & 0x80808080) == (DATA & 0x80808080))
			break;
		
		// Check time over - D5 bit
		if((status & 0x20202020) == 0x20202020)
		{
			//	Time over!
			status = HWEXTBUS(ADR);
			if((status & 0x80808080) == (DATA & 0x80808080))	
				break;
			else	
				return flashFault;
		}
		
		//	Check D6
//		status_last = status;
//		status = HWEXTBUS(ADR);
//		if (status != status_last)
//		{
//			if (D6_Stopped)
//				return flashFault;
//			else
//				D6_Stopped = 1;
//		}			
	}	
	
  return flashOk;
}

FlashStatus WaitProgressBit_D6(uint32_t ADR)
{
	volatile uint32_t status, status_last;

	while(1)
	{	
		status_last = HWEXTBUS(ADR);
		status = HWEXTBUS(ADR);
		if(status == status_last)
			break;
		
		//	Check timeover
		if((status & 0x20202020) == 0x20202020)
		{
			status_last = HWEXTBUS(ADR);
			status = HWEXTBUS(ADR);
			if (status == status_last) 
				break;
			else	
				return flashFault;
		}
	}
	return flashOk;	
}

FlashStatus EraseFLASHSector(uint32_t SectorInd)
{
	FlashStatus result;
	
	HWEXTBUS(0x555) = 0xAAAAAAAA;
	HWEXTBUS(0x2AA) = 0x55555555;
	HWEXTBUS(0x555) = 0x80808080;
	HWEXTBUS(0x555) = 0xAAAAAAAA;
	HWEXTBUS(0x2AA) = 0x55555555;
	
	HWEXTBUS(SectorInd << 16) = 0x30303030;	
	
	result = WaitProgressBit_D6(SectorInd << 16);
	
	return result;		
}

