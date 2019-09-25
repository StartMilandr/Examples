#include <MDR32F9Qx_port.h>
#include <MDR32F9Qx_rst_clk.h>

#define VD6 PORT_Pin_7
#define VD7 PORT_Pin_8
#define VD8 PORT_Pin_9
#define VD9 PORT_Pin_10
#define VD10 PORT_Pin_11
#define VD11 PORT_Pin_12
#define VD12 PORT_Pin_13
#define VD13 PORT_Pin_14
#define LED_ALL VD6 | VD7 | VD8 | VD9 | VD10 | VD11 | VD12 | VD13
#define ErrorButtons PORT_Pin_5 | PORT_Pin_8 | PORT_Pin_10 | PORT_Pin_15
#define codeON 0xAA
#define codeOFF 0xBB
#define codeERROR 0xEE

void ClkConfig(void);
void PortConfig(void);
void UARTConfig(void);
void UART1_Handler(void);
void Delay(int waitTicks);



int main()
{
	ClkConfig();
	UARTConfig();
	PortConfig();
	NVIC_EnableIRQ(UART1_IRQn);			//Enable UART1 interrupt
	while(1)
	{
		if (PORT_ReadInputDataBit(MDR_PORTE, PORT_Pin_9) == Bit_RESET)
    {
      	PORT_SetBits(MDR_PORTD, LED_ALL);
				Delay(500000);
				PORT_ResetBits(MDR_PORTD, LED_ALL);
			  MDR_UART1->DR=codeON; // Code on diods
			
    }
    else
    {
      	if (PORT_ReadInputDataBit(MDR_PORTE, PORT_Pin_11) == Bit_RESET)
    {
      	PORT_SetBits(MDR_PORTD, LED_ALL);
				Delay(500000);
				PORT_ResetBits(MDR_PORTD, LED_ALL);
			  MDR_UART1->DR=codeOFF; // Code off diods
    }
		else 
		{
			if ((PORT_ReadInputDataBit(MDR_PORTE, PORT_Pin_5) == Bit_RESET) || (PORT_ReadInputDataBit(MDR_PORTE, PORT_Pin_8) == Bit_RESET)
				|| (PORT_ReadInputDataBit(MDR_PORTE, PORT_Pin_10) == Bit_RESET)|| (PORT_ReadInputDataBit(MDR_PORTE, PORT_Pin_15) == Bit_RESET))
			{
				PORT_SetBits(MDR_PORTD, LED_ALL);
				Delay(500000);
				PORT_ResetBits(MDR_PORTD, LED_ALL);
			  MDR_UART1->DR=codeERROR; // Code off diods
			}
		}
    }
	};
}


//--- Clock configuration ---
void ClkConfig()
{
	MDR_RST_CLK ->HS_CONTROL = 0x00000001;			//HSE - On; Oscillator mode
	while((MDR_RST_CLK ->CLOCK_STATUS&0x04)!=0x04);	//Wait until HSE not ready
	MDR_RST_CLK ->PER_CLOCK|=0x08;					//EEPROM_CTRL Clock enable
	MDR_EEPROM -> CMD = 0;
	MDR_RST_CLK ->PER_CLOCK&=(~0x08);				//EEPROM_CTRL Clock disable
  MDR_RST_CLK ->CPU_CLOCK = 0x00000102;			//CPU Clock = HSE (8MHz)
	MDR_RST_CLK ->PER_CLOCK|=(1<<6)|(1<<23)|(1<<24)|(1<<25); //clock of UART1, PORTC, PORTD On
	MDR_RST_CLK ->UART_CLOCK=1<<24;					//enable CLK of UART1, F_UART1=HCLK
}

//--- Ports configuration ---
void PortConfig()
{
	// Config port E for Buttons
	PORT_InitTypeDef PORT_InitStructure;
	PORT_InitStructure.PORT_Pin = (PORT_Pin_9 | PORT_Pin_11 | ErrorButtons);
	PORT_InitStructure.PORT_OE = PORT_OE_IN;
	PORT_InitStructure.PORT_FUNC = PORT_FUNC_PORT;
	PORT_InitStructure.PORT_MODE = PORT_MODE_DIGITAL;
	PORT_InitStructure.PORT_SPEED = PORT_SPEED_SLOW;
	PORT_Init(MDR_PORTE, &PORT_InitStructure);
	//*** Config port D for Leds ***
	PORT_InitTypeDef GPIOInitStruct;
  PORT_StructInit(&GPIOInitStruct);
	GPIOInitStruct.PORT_Pin        = LED_ALL;
  GPIOInitStruct.PORT_OE         = PORT_OE_OUT;
  GPIOInitStruct.PORT_SPEED      = PORT_SPEED_SLOW;
  GPIOInitStruct.PORT_MODE       = PORT_MODE_DIGITAL;
  PORT_Init(MDR_PORTD, &GPIOInitStruct);
	//*** Config port C for SIR UART1 ***
	MDR_PORTC->FUNC = 0x00003C0;
	MDR_PORTC->ANALOG = 0x0018;
	MDR_PORTC->PWR = 0x000003C0;
	
}

//--- UART configuration ---
void UARTConfig()
{
	MDR_UART1->IBRD=0x0004;	// speed of UART1 = 115200 bit/s
	MDR_UART1->FBRD=0x0016;	// speed of UART1 = 115200 bit/s
	MDR_UART1->ILPR=0x0004;
	MDR_UART1->ICR=1<<4;		// clear Rx_interrupt_flag
	MDR_UART1->IMSC=0x0010;		// Rx interrupt enable
	MDR_UART1->LCR_H=0x0060;	// 8-bits word, FIFO disable, parity disable, 1 stop bit
	MDR_UART1->CR=0x0303;		// UART1 - SIR, Tx, Rx enable
}

//--- UART1 interrupt routine ---
void UART1_Handler()
{
	MDR_UART1->ICR = 0x10;
	uint32_t i, temp[16];
	for (i=0;i<16; i++)
	temp[i]=MDR_UART1->DR;
	
	switch (MDR_UART1->DR)
	{
		case codeON: 
			PORT_SetBits(MDR_PORTD, LED_ALL);	// LED ON
			Delay(50000);
		break;
		case codeOFF:
			PORT_ResetBits(MDR_PORTD, LED_ALL);	// LED OFF
			Delay(50000);
		break;
		default:
			for (i=0;i<8; i++)
		{
			PORT_SetBits(MDR_PORTD, LED_ALL);	
			Delay(50000);
			PORT_ResetBits(MDR_PORTD, LED_ALL);	
			Delay(50000);
		}
		break;
		
	}
		
}

void Delay(int waitTicks)
{
  int i;
  for (i = 0; i < waitTicks; i++)
  {
    __NOP();
  }	
}

