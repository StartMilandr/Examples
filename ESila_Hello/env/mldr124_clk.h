/**
  ******************************************************************************
  * @file    mldr124_clk.h
  * @version V1.0.0
  * @date    19/10/2018
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MLDR124_CLK_H
#define __MLDR124_CLK_H

/* Includes ------------------------------------------------------------------*/
#include "mldr124_config.h"

#define MAX_CLK_HSI                     0      
#define MAX_CLK_HSI_DV2                 1
#define MAX_CLK_HSE0                    2
#define MAX_CLK_HSE0_DV2                3
#define MAX_CLK_HSE1                    4
#define MAX_CLK_HSE1_DV2                5
#define MAX_CLK_LSI                     6     
#define MAX_CLK_LSE                     7 
#define MAX_CLK_PLL0                    8      
#define MAX_CLK_PLL1                    9 
#define MAX_CLK_PLL2                    10 
#define MAX_CLK_PLL3                    11       

#define PLL_CLK_HSI                     0      
#define PLL_CLK_HSI_DV2                 1
#define PLL_CLK_HSE0                    2
#define PLL_CLK_HSE0_DV2                3
#define PLL_CLK_HSE1                    4
#define PLL_CLK_HSE1_DV2                5

#define PLL_DV_NONE                     0
#define PLL_DV_2                        1
#define PLL_DV_4                        2      
      
#define CLK_SOURSE_HSI                  0
#define CLK_SOURSE_HSE0                 1
#define CLK_SOURSE_HSE1                 2
#define CLK_SOURSE_LSI                  3
#define CLK_SOURSE_LSE                  4
#define CLK_SOURSE_PLL0                 5
#define CLK_SOURSE_PLL1                 6
#define CLK_SOURSE_PLL2                 7
#define CLK_SOURSE_PLL3                 8
#define CLK_SOURSE_MAX_CLK              13

#define CLK_LSE                         0
#define CLK_HSE0                        1
#define CLK_HSE1                        2

#define CLK_XSE_OFF                     0
#define CLK_XSE_Bypass                  4
#define CLK_XSE_ON                      8

uint32_t CLK_GetSourceClk( uint8_t sourse );
void CLK_XSEConfig( uint32_t xse, uint32_t state );
uint32_t CLK_XSEWaitReady( uint32_t xse );

uint32_t CLK_SetPllClk( MDR_CLK_TypeDef *pll, uint8_t source, uint32_t clock );
void CLK_PllConfig( MDR_CLK_TypeDef *pll, uint32_t source, uint16_t n, uint8_t q, uint8_t dv );
void CLK_PllState( MDR_CLK_TypeDef *pll, FunctionalState NewState );
uint32_t CLK_PLLWaitReady( MDR_CLK_TypeDef *pll );
#endif /* __MLDR124_CLK_H */
