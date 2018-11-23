#include <MDR32F9Qx_port.h>
#include "brdLCD.h"
#include "brdUtils.h"

static char message[] = "  Hello World!  ";

int main(void)
{
  static uint8_t strLength;
  strLength = (uint8_t) strlen(message);  
  
  BRD_LCD_Init();
  
  while (1)
  {
    BRD_LCD_ScrollStringLeft(message, 5, strLength);  
    Delay(800000);
  }
}
