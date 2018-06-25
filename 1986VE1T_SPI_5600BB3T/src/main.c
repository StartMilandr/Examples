#include "brdClock.h"
#include "brdBtn.h"
#include "brdLed.h"
#include "brdUtils.h"
#include "_brdSPI_Select.h"

#include "5600VV3T.h"

#define MASTER_MODE 1 

MAC_StringTypeDef MAC_Table[2048]; // Массив структур
MAC_StringTypeDef MAC_String;
MAC_StringTypeDef MAC_String1;

int main(void)
{
	uint32_t i = 0, j = 0;
	uint16_t N[2048];

  // Clock
  BRD_Clock_Init_HSE_PLL(10); // 80MHz
  
  //  SPI Init
  BRD_SPI_PortInit(pBRD_SPIx);
  BRD_SPI_Init(pBRD_SPIx, MASTER_MODE);
	
	MAC_String.MAC = 0x227812CD236F;
	MAC_String.OLD_CNT = 0x234;
	MAC_String.VALID = 0x1;
	MAC_String.PORT_NUM = 0x2;

	TXRX_Data(pBRD_SPIx, AGE_CONTROL_0, WRITE, 0x6F); // Отключение удаления записей из MAC-таблицы при достижении счётчиком старения значения 0xFFF
	
	Write_MAC_String(pBRD_SPIx, Get_Addr(MAC_String, 0x5), &MAC_String); // Запись строки в MAC таблицу
	
	Read_MAC_String(pBRD_SPIx, Get_Addr(MAC_String, 0x5), &MAC_String1); // Чтение строки из MAC таблицы
	
	Read_MAC_Table(pBRD_SPIx, MAC_Table); // Чтение всей MAC-таблицы
	
	
	for(i=0;i<2048;i++) // Определение адресов строк с активными записями
	{
		if(MAC_Table[i].VALID != 0)
		{
			N[j] = i;
			j++;
		}
	}
	
  while (1) {}
}

