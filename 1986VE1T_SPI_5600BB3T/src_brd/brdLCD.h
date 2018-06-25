/*******************************************************************************
 * @File: lcd.h
 * @Author: Milandr, L.
 * @Project: Generic
 * @Microcontroller: 1986VE92U
 * @Device: Evaluation Board For MCU 1986VE92U
 * @Date: 22.03.2017
 * @Purpose: Библиотека для работы с дисплеем MT-12864J
 *******************************************************************************/

// Подключение заголовочных файлов
#include <MDR32F9Qx_port.h>
#include <MDR32F9Qx_rst_clk.h>
// Стандартные библиотеки языка Си
#include <string.h>
#include <stdio.h>

#include "brdLCD_Font.h"

#include "brdDef.h"

//  Необходимые для вывода
#define BRD_LCD_Init    LCD_Initialize
#define BRD_LCD_Print   LCD_PutString


// Прототипы функций
void    LCD_ConfigureGPIO(void);
void    LCD_Initialize       (void);                                                 // Инициализация дисплея
void    LCD_Delay            (uint32_t value);                                       // Задержка
void    LCD_DataBusDirection (uint8_t direction);                                    // Выбор направления шины данных
void    LCD_SetDataBits      (uint8_t value);                                        // Передача информации на шину данных
void    LCD_Reset            (uint8_t chip);                                         // Возврат выводов в исходное состояние
void    LCD_Enable           (uint8_t chip);                                         // Включение дисплея
void    LCD_Disable          (uint8_t chip);                                         // Выключение дисплея
uint8_t LCD_ReadStatus       (uint8_t chip);                                         // Получение статуса операции
void    LCD_SetPage          (uint8_t chip, uint8_t page);                           // Выбор страницы
void    LCD_SetAddress       (uint8_t chip, uint8_t address);                        // Выбор адреса колонки
void    LCD_WriteData        (uint8_t chip, uint8_t data);                           // Запись данных в ОЗУ дисплея
uint8_t LCD_ReadData         (uint8_t chip);                                         // Чтение данных из ОЗУ дисплея
void    LCD_ClearPage        (uint8_t chip, uint8_t page);                           // Очистка страницы
void    LCD_ClearScreen      (uint8_t chip);                                         // Очистка дисплея
void    LCD_PutSymbol        (uint8_t symbol, int32_t x, int32_t y);                 // Вывод символа
void    LCD_PutString        (const char* string, int32_t y);                        // Вывод строки
void    LCD_ScrollString     (const char* string, int32_t y, int32_t shift);         // Горизональное перемещение строки
void    LCD_PutImage         (const uint8_t* image, int32_t top,    int32_t left,    // Вывод изображения
                                                    int32_t bottom, int32_t right);
//  Pattern for usage 
//void LCD_ShowDelay(uint32_t presc, uint32_t delay)
//{
//  static char message[64];
//  
//  sprintf(message , "PSC=%d  T=%d ", presc, delay);
//  BRD_LCD_Print (message, 3);
//}
