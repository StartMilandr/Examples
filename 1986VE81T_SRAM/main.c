/* Includes ------------------------------------------------------------------*/
#include "MDR1986VE8T.h"
#include "spec.h"
#include "mdr32f8_config.h"
#include "mdr32f8_port.h"
#include "mdr32f8_clkctrl.h"

/* Private typedef -----------------------------------------------------------*/
PORT_InitTypeDef PORT_InitStructure;

/* Private define ------------------------------------------------------------*/
#define VD7 PORT_Pin_16
#define VD8 PORT_Pin_17
#define VD9 PORT_Pin_18

#define LED_SHOW_DELAY  200000

void Delay(__IO uint32_t nCount)
{
  for (; nCount != 0; nCount--);
}

int main(void)
{	
  /* Выключение блока сброса предназначенного для выработки аппаратного сброса при включении основного питания */
  POR_disable();
	
  /* Функция установки CLKCTRL по умолчанию */
  CLKCTRL_DeInit();
	
  /* Функция конфигурирования HSE0 clock */
  CLKCTRL_HSEconfig(CLKCTRL_HSE0_CLK_ON);
  while(CLKCTRL_HSEstatus(CLKCTRL_HSEn_STAT_HSE0_RDY) != SUCCESS){}
	
  /* Конфигурирование блока умножения тактовой частоты */
  CLKCTRL_CPU_PLLconfig(PLL0, CLKCTRL_PLLn_CLK_SELECT_HSE0div1, 0, 4);//PLLn, SRC, Q, N
  while(CLKCTRL_CPU_PLLstatus(0) != SUCCESS){}
  CLKCTRL_MAX_CLKSelection(CLKCTRL_MAX_CLK_PLL0);	
			
  /* Тактирование порта PORTC */
  CLKCTRL_PER0_CLKcmd(CLKCTRL_PER0_CLK_MDR_PORTC_EN, ENABLE);

  /* Ключи записи в регистры порта */
  KEY_reg_accs();

  /* Конфигурация PORTC пинов [16:18] */
  PORT_InitStructure.PORT_Pin   = (VD7 | VD8 | VD9);
  PORT_InitStructure.PORT_SOE    = PORT_SOE_OUT;
  PORT_InitStructure.PORT_SANALOG  = PORT_SANALOG_DIGITAL;
  PORT_InitStructure.PORT_SPD = PORT_SPD_OFF;
  PORT_InitStructure.PORT_SPWR = PORT_SPWR_10;
			
  /*Применяем структуру*/
  PORT_Init(PORTC, &PORT_InitStructure);
		
  /*Основной цикл*/									
   while (1)
	{
    PORT_SetBits(PORTC, VD7);   //зажигаем диод
	  Delay(LED_SHOW_DELAY);
    PORT_ResetBits(PORTC, VD7); //гасим диод
    
	  Delay(LED_SHOW_DELAY);
    PORT_SetBits(PORTC, VD8);
	  Delay(LED_SHOW_DELAY);
    
    PORT_ResetBits(PORTC, VD8);
	  Delay(LED_SHOW_DELAY);
    PORT_SetBits(PORTC, VD9);
    
	  Delay(LED_SHOW_DELAY);
    PORT_ResetBits(PORTC, VD9);
	  Delay(LED_SHOW_DELAY);
	}
}
