#include "EEPROM_Test.h"
#include "brdDef.h"
#include "brdLed.h"
#include "brdBtn.h"

#define LED_OK        (BRD_LED_1 | BRD_LED_2)
#define LED_ERR_CLR   BRD_LED_1
#define LED_ERR_WRRD  BRD_LED_2
#define LED_CLR				(BRD_LED_1 | BRD_LED_2)

int main()
{
	BRD_LEDs_Init();
	BRD_BTNs_Init();
	
	while	(1)
	{
	  if (BRD_Is_BntAct_Up())
		{
			while (BRD_Is_BntAct_Up());
	
	    BRD_LED_Set(LED_CLR, 0);			
			
		  switch (EEPROM_Test_WR_RD(5))
			{
				case ST_OK: 
					BRD_LED_Set(LED_OK, 1);
					break;
				case ST_CLR_ERR: 
					BRD_LED_Set(LED_ERR_CLR, 1);
					break;
				case ST_WR_RD_ERR: 
					BRD_LED_Set(LED_ERR_WRRD, 1);
					break;
			}		
		
		}
	
	};
	
}	
