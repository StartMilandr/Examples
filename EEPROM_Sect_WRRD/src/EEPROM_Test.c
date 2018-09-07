#include <MDR32F9Qx_port.h>
#include <MDR32F9Qx_rst_clk.h>
#include <MDR32F9Qx_eeprom.h>

#include "EEPROM_Test.h"

#if defined ( USE_MDR1986VE9x )
	#define EEPROM_PAGE_START							0x08000000
#elif defined (USE_MDR1986VE1T)
	#define EEPROM_PAGE_START             0x00000000

#else
	'Неподдерживаемый процессор'
#endif


#define EEPROM_PAGE_SIZE             (4*1024)
//#define MAIN_EEPAGE                  5

/* Private functions ---------------------------------------------------------*/
uint32_t Pseudo_Rand(uint32_t addr)
{
  uint32_t hash = 0;
  uint32_t i = 0;
  uint8_t* key = (uint8_t *)&addr;

  for (i = 0; i < 4; i++)
  {
    hash += key[i];
    hash += (hash << 10);
    hash ^= (hash >> 6);
  }

  for (i = 0; i < 256; i++)
  {
    hash += (hash << 10);
    hash ^= (hash >> 6);
  }

  hash += (hash << 3);
  hash ^= (hash >> 11);
  hash += (hash << 15);
  return hash;
}

void Delay(void)
{
  volatile uint32_t i = 0;
  for (i = 0; i < 100000; i++)
  {
  }
}

EEPROM_TST_STATUS EEPROM_Test_WR_RD (int32_t testPage)
{
  uint32_t Address = 0;
  uint32_t BankSelector = 0;
  uint32_t Data = 0;
  uint32_t i = 0;

  /* Enables the clock on EEPROM */
  RST_CLK_PCLKcmd(RST_CLK_PCLK_EEPROM, ENABLE);

  /* Erase main memory page MAIN_EEPAGE */
  Address = EEPROM_PAGE_START + testPage * EEPROM_PAGE_SIZE;
  BankSelector = EEPROM_Main_Bank_Select;
  EEPROM_ErasePage (Address, BankSelector);

  /* Check main memory page MAIN_EEPAGE */
  Data = 0xFFFFFFFF;
  for (i = 0; i < EEPROM_PAGE_SIZE; i += 4)
  {
    if (EEPROM_ReadWord (Address + i, BankSelector) != Data)
    {
			return ST_CLR_ERR;
    }
  }

  /* Fill main memory page MAIN_EEPAGE */
  Address = EEPROM_PAGE_START + testPage * EEPROM_PAGE_SIZE;
  BankSelector = EEPROM_Main_Bank_Select;
  for (i = 0; i < EEPROM_PAGE_SIZE; i += 4)
  {
    Data = Pseudo_Rand (Address + i);
    EEPROM_ProgramWord (Address + i, BankSelector, Data);
  }

  /* Check main memory page MAIN_EEPAGE */
  Address = EEPROM_PAGE_START + testPage * EEPROM_PAGE_SIZE;
  BankSelector = EEPROM_Main_Bank_Select;
  for (i = 0; i < EEPROM_PAGE_SIZE; i +=4 )
  {
    Data = Pseudo_Rand (Address + i);
    if (EEPROM_ReadWord (Address + i, BankSelector) != Data)
    {
			return ST_WR_RD_ERR;
    }
  }

  /* Erase main memory page MAIN_EEPAGE */
  Address = EEPROM_PAGE_START + testPage * EEPROM_PAGE_SIZE;
  BankSelector = EEPROM_Main_Bank_Select;
  EEPROM_ErasePage (Address, BankSelector);

  /* Check main memory page MAIN_EEPAGE */
  Data = 0xFFFFFFFF;
  for (i = 0; i < EEPROM_PAGE_SIZE; i += 4)
  {
    if (EEPROM_ReadWord (Address + i, BankSelector) != Data)
    {
			return ST_CLR_ERR;
    }
  }

	return ST_OK;
}
