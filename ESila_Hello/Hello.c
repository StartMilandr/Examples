#include "mldr124.h"
#include "mldr124_clk.h"
#include "mldr124_port.h"
#include "stdio.h"
	
#define ITM_Port8(n)    (*((volatile unsigned char *)(0xE0000000+4*n)))
#define ITM_Port16(n)   (*((volatile unsigned short*)(0xE0000000+4*n)))
#define ITM_Port32(n)   (*((volatile unsigned long *)(0xE0000000+4*n)))

#define DEMCR           (*((volatile unsigned long *)(0xE000EDFC)))
#define TRCENA          0x01000000
	
#define LedGreen PORT_Pin_17
#define LedBlue PORT_Pin_19
#define LedRed PORT_Pin_21

void vError(void)
{
	PORT_SetBits(PORTC, LedRed);
	while(1);
}

void Delay(uint32_t waitTicks)
{
	uint32_t i;
	for (i = 0; i < waitTicks; i++);
}

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
	// Setting PORTC for diods
	PORT_InitTypeDef LedPort;
	
  CLK_CNTR->KEY = 0x8555AAA1;
  CLK_CNTR->PER0_CLK |=  1<<15; // PORTC EN
  PORTC->KEY = 0x8555AAA1;
	PORT_DeInit(PORTC);
  PORT_StructInit( &LedPort ); 
  LedPort.PORT_Pin     = LedGreen | LedBlue | LedRed;
  LedPort.PORT_SOE     = PORT_SOE_OUT;
	LedPort.PORT_SFUNC   = PORT_SFUNC_PORT;
	LedPort.PORT_SANALOG = PORT_SANALOG_DIGITAL;
  LedPort.PORT_SPWR    = PORT_SPWR_300;
  PORT_Init( PORTC, &LedPort );
	
	
  CLK_CNTR->KEY = 0x8555AAA1;
  CLK_CNTR->PER0_CLK =  0xFFFFFFFF;
  CLK_CNTR->PER1_CLK =  0xFFFFFFFF;
	// Setting work HSE and currents
	CLK_CNTR->PER1_CLK |=  1<<26; 
	COMP0->ANABG_CTRL=0x00000081; 
  BKP->KEY = 0x8555AAA1;
	CLK_XSEConfig( CLK_HSE0, CLK_XSE_ON );
	
	if( !CLK_XSEWaitReady( CLK_HSE0 ) )
		vError();
	CLK_CNTR->MAX_CLK = MAX_CLK_HSE0;
	printf("Hello!\n");

	while (1) 
	{
		PORT_SetBits(PORTC, LedRed);
		Delay(500000);
		PORT_ResetBits(PORTC, LedRed);
		PORT_SetBits(PORTC, LedGreen);
		Delay(500000);
		PORT_ResetBits(PORTC, LedGreen);
		PORT_SetBits(PORTC, LedBlue);
		Delay(500000);
		PORT_ResetBits(PORTC, LedBlue);
	}
	
}
