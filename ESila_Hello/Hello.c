#include ".\env\cm4ikmcu.h"

#include "stdio.h"
	
#define ITM_Port8(n)    (*((volatile unsigned char *)(0xE0000000+4*n)))
#define ITM_Port16(n)   (*((volatile unsigned short*)(0xE0000000+4*n)))
#define ITM_Port32(n)   (*((volatile unsigned long *)(0xE0000000+4*n)))

#define DEMCR           (*((volatile unsigned long *)(0xE000EDFC)))
#define TRCENA          0x01000000

struct __FILE { int handle; /* Add whatever is needed */ };
FILE __stdout;
FILE __stdin;

int fputc(int ch, FILE *f) {
  if (DEMCR & TRCENA) {
    while (ITM_Port32(0) == 0);
    ITM_Port8(0) = ch;
  }
  return(ch);
}	

int main(void)
{
	int i;
	
  CLK_CNTR->KEY = 0x8555AAA1;
  CLK_CNTR->PER0_CLK =  0xFFFFFFFF;
  CLK_CNTR->PER1_CLK =  0xFFFFFFFF;

	PORTA->KEY = 0x8555AAA1;
  PORTA->SANALOG = 0xFFFFFFFF;
  PORTA->SPWR[1] = 0x55555555;
  PORTA->SPWR[0] = 0x55555555;
  PORTA->CFUNC[3] = 0xFFFFFFFF;
  PORTA->CFUNC[2] = 0xFFFFFFFF;
  PORTA->CFUNC[1] = 0xFFFFFFFF;
  PORTA->CFUNC[0] = 0xFFFFFFFF;
  PORTA->SOE = 0xFFFFFFFF;
	printf("Hello!\n");

	SysTick->LOAD = 500; // PA5 = CLK/500/2
	SysTick->CTRL = 0x5; //CLKSOURCE = HCLK,Enable
	while (1) 
	{
		if (SysTick->CTRL&1<<16)
		{
			PORTA->RXTX = i++ << 5; // PA5..PA31
		}
	}
	
}
