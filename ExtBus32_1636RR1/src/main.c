#include <MDR32F9Qx_port.h>
#include <MDR32F9Qx_rst_clk.h>

#include "brdDef.h"
#include "brdClock.h"
#include "brdBtn.h"
#include "brdLed.h"
#include "brdExtBus.h"
#include "brdFlash_ExtBus.h"

// ТОЛЬКО ДЛЯ 1986ВЕ1
// На одной плате 1636РР1 из двух, без этого не работало
// Данные D0-D1 совмещены с выводами MODE и эти выводы (три бита) при проверке на стертость возвращают 0
// Хотя при вторичном считывании читались 1
// При внесении емкости щупом осциллографа на вывод D0 сбои пропадали.
// Вторая плата работает сразу, в первой видимы где-то плохой контакт.
// Опция оставлена для возможности отладки в будущем, по умолчанию выключена.
#define USE_VE1_BRD_FIX  0


#define LED1_CYCLE         BRD_LED_1
#define LED2_OK     			 BRD_LED_2
#define LED3_ERAZE_ERR     BRD_LED_3
#define LED4_PROG_ERR      BRD_LED_4

#define LED_PERIOD			30000
#define LED_PERIOD_TEST	2000

//	A[18] pulled up to GND in the Board!
#define MEM_SECT_COUNT 	4
#define MEM_SECT_SIZE 	0x10000
#define MEM_SIZE 				(MEM_SECT_SIZE * 4)

typedef enum {resOk, resEraseFault, resProgFault, resComError} TestResult;

typedef enum {noTask, testFlashFull, testFlashBySect} TestTask;

TestResult FlashEraseAndTest(void);
TestResult TestFlash_WR_RD(uint32_t startAddr, uint32_t dataCount, uint32_t modeInv);
TestResult TestFlashFull(void);
TestResult TestFlashBySect(void);
TestResult TestFlashSector(uint32_t sectorInd);

void LedShowCycle(uint32_t period);


TestResult res = resComError;
TestTask   task = noTask;

void While_Test_1636RR_VC1(void);
void While_Test_1636RR(void);

int main()
{
  BRD_Clock_Init_HSE_dir();


#ifdef USE_BOARD_VC1
	BRD_ExtBus_InitPins_A20_D32();
	BRD_ExtBus_Init();
  
  While_Test_1636RR_VC1();
#else  
  // Пины используются внешней шиной - тест только в отладчике
  BRD_LEDs_Init();
	BRD_BTNs_Init();
  
	BRD_ExtBus_InitPins_A20_D32();
	BRD_ExtBus_Init();  
  
  While_Test_1636RR();
#endif

}

void While_Test_1636RR_VC1(void)
{
  while(1)
  {
    //	Perform test
    if (task != noTask)
    {				
      // Perform test
      if (task == testFlashFull)
        res = TestFlashFull();
      else
        res = TestFlashBySect();
      task = noTask;
  }
  }
}

void While_Test_1636RR(void)
{
	while (1)
	{	
// Пины используются внешней шиной
    
		//	SELECT btn runs EraseFull
		if (BRD_Is_BntAct_Select())
		{
			while (BRD_Is_BntAct_Select()) {};
				
			if (task == noTask)
				task = testFlashFull;				
		}		
		
		//	UP btn runs EraseFull
		if (BRD_Is_BntAct_Up())
		{
			while (BRD_Is_BntAct_Up()) {};
				
			if (task == noTask)
				task = testFlashBySect;				
		}				
    
		//	Perform test
		if (task != noTask)
		{	
			//	Show test started - Leds On
			BRD_LED_Set(LED1_CYCLE | LED2_OK | LED3_ERAZE_ERR | LED4_PROG_ERR, 1);
				
			// Perform test
			if (task == testFlashFull)
				res = TestFlashFull();
			else
			  res = TestFlashBySect();
			task = noTask;
				
			//	Show test finished - Leds Off
			BRD_LED_Set(LED1_CYCLE | LED2_OK | LED3_ERAZE_ERR | LED4_PROG_ERR, 0);

			//	Show Test Result
			switch (res)
			{
			case resEraseFault:
				BRD_LED_Set(LED3_ERAZE_ERR, 1);
				break;
			case resProgFault:
				BRD_LED_Set(LED4_PROG_ERR, 1);
				break;
			case resComError:
				BRD_LED_Set(LED3_ERAZE_ERR | LED4_PROG_ERR, 1);
				break;				
			default:
				BRD_LED_Set(LED2_OK, 1);
			}	
		}	

		LedShowCycle(LED_PERIOD);		
	}
}

void LedShowCycle(uint32_t period)
{
	static uint32_t i = 0;
	
	i++;		
	if (i > period)
	{	
		BRD_LED_Switch(LED1_CYCLE);
		i = 0;
	}	
}	

TestResult TestFlashBySect(void)
{
	TestResult res = resComError;
	uint32_t sectInd;

	for (sectInd = 0; sectInd < MEM_SECT_COUNT; sectInd++)	
	{
		res =	TestFlashSector(sectInd);
		if (res != resOk)
			break;
	}
	
	return res;
}			

TestResult TestFlashSector(uint32_t sectorInd)
{
	uint32_t i;
	
//	--- Test by i	 ---
	BRD_LED_Switch(LED1_CYCLE);	
	
	//	Erase Sector
	if (EraseFLASHSector(sectorInd) != flashOk)
		return resComError;
	//	Check Clear
	for(i = 0; i < MEM_SECT_SIZE; i++ )
		if(ReadFLASH(MEM_SECT_SIZE * sectorInd + i) != 0xFFFFFFFF)
			return resEraseFault;	
	
	//	Write Values
	for(i = 0; i < MEM_SECT_SIZE; i++ )	
		if ((WriteFLASH(MEM_SECT_SIZE * sectorInd + i, i)) != flashOk)
			return resComError;
		
	//  Read and Check Values
	for(i = 0; i < MEM_SECT_SIZE; i++ )	
		if(ReadFLASH(MEM_SECT_SIZE * sectorInd + i) != i)
			return resProgFault;
		
//	---- Test by ~i		---
	BRD_LED_Switch(LED1_CYCLE);		

	//	Erase Sector
	if (EraseFLASHSector(sectorInd) != flashOk)
		return resComError;
	//	Check Clear
	for(i = 0; i < MEM_SECT_SIZE; i++ )
		if(ReadFLASH(MEM_SECT_SIZE * sectorInd + i) != 0xFFFFFFFF)
			return resEraseFault;	
	
	//	Write Values
	for(i = 0; i < MEM_SECT_SIZE; i++ )	
		if ((WriteFLASH(MEM_SECT_SIZE * sectorInd + i, ~i)) != flashOk)
			return resComError;
		
	//  Read and Check Values
	for(i = 0; i < MEM_SECT_SIZE; i++ )	
		if(ReadFLASH(MEM_SECT_SIZE * sectorInd + i) != ~i)
			return resProgFault;
			
	return resOk;	
}


TestResult FlashEraseAndTest(void)
{
	uint32_t i;
  volatile uint32_t value;
	
	if (EraseFullFLASH() != flashOk)
	  return resComError;
	
	//	Check Memory Clear
	for (i = 0; i < MEM_SIZE; i++)
	{
#if USE_VE1_BRD_FIX
    //  Двойное считывание
    value = ReadFLASH(i);
		if (value != 0xFFFFFFFF)
    {  
      value = ReadFLASH(i);
      if (value != 0xFFFFFFFF)
			  return resEraseFault;
    }    
#else    
    //  Одинарное считывание
    if (ReadFLASH(i) != 0xFFFFFFFF)
			  return resEraseFault;
#endif
	}	
	return resOk;
}	

TestResult TestFlashFull(void)
{
	TestResult result;
	uint32_t modeInv;
	
	for (modeInv = 0; modeInv <= 1; ++modeInv)
	{
		//	Erase
		result = FlashEraseAndTest();
		if (result != resOk)
			break;

		//	Addr: 0 - 0x40000
		result = TestFlash_WR_RD(0, MEM_SIZE, modeInv);
		if (result != resOk)
			break;	
	}	
	
	return result;
}	

TestResult TestFlash_WR_RD(uint32_t startAddr, uint32_t dataCount, uint32_t modeInv)
{	
	uint32_t i = 0;
	uint32_t rdData;
	uint32_t wrData;

	//	Test WR-RD
	for (i = 0; i < dataCount; i++)
	{	
		if (modeInv == 0)
			wrData = i;
		else
			wrData = ~i;

		if (WriteFLASH(startAddr + i, wrData) != flashOk)
			return resComError;

		rdData = ReadFLASH(startAddr + i);
		
		//	Check result
		if (rdData != wrData)
      return resProgFault;
		
		//	Led Update
		LedShowCycle(LED_PERIOD_TEST);
	}
	
	return resOk;
}	

	
