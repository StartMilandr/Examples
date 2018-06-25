/*******************************************************************************
 * @File: lcd.c
 * @Author: Milandr, L.
 * @Project: Generic
 * @Microcontroller: 1986VE92U
 * @Device: Evaluation Board For MCU 1986VE92U
 * @Date: 22.03.2017
 * @Purpose: Библиотека для работы с дисплеем MT-12864J
 *******************************************************************************/

// Подключение заголовочного файла
#include "brdLCD.h"

// Строка, выводимая на индикатор при инициализации
static const char* header = "   \xC0\xCE \"\xCC\xE8\xEB\xE0\xED\xE4\xF0\"";  // АО "Миландр"

// Изображение, выводимое на индикатор при инициализации (эмблема "Миландр")
static const uint8_t logo[32] =
{
  0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0x7E, 0x1E, 0x06,
  0x06, 0x1E, 0x7E, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE,
  0x7F, 0x5F, 0x47, 0x41, 0x7C, 0x78, 0x70, 0x60,
  0x60, 0x70, 0x78, 0x7C, 0x41, 0x47, 0x5F, 0x7F
};


// Константы, определяющие направление шины данных
#define OUT 0
#define IN  1

// Ширина дисплея (в символах 8x8)
#define LCD_SCREEN_WIDTH 16

// Директивы для работы с выводами дисплея
// Вывод E1 (выбор кристалла 1)
#define LCD_ClearBit_E1   PORT_ResetBits(BRD_LCD_E1_PORT, BRD_LCD_E1_PIN)
#define LCD_SetBit_E1     PORT_SetBits  (BRD_LCD_E1_PORT, BRD_LCD_E1_PIN)

// Вывод E2 (выбор кристалла 2)
#define LCD_ClearBit_E2   PORT_ResetBits(BRD_LCD_E2_PORT, BRD_LCD_E2_PIN)
#define LCD_SetBit_E2     PORT_SetBits  (BRD_LCD_E2_PORT, BRD_LCD_E2_PIN)

// Вывод RES (сброс)
#ifdef BRD_LCD_RES_PORT
  #define LCD_ClearBit_RES  PORT_ResetBits(BRD_LCD_RES_PORT, BRD_LCD_RES_PIN)
  #define LCD_SetBit_RES    PORT_SetBits  (BRD_LCD_RES_PORT, BRD_LCD_RES_PIN)
#else
  #define LCD_ClearBit_RES  __nop()
  #define LCD_SetBit_RES    __nop()
#endif

// Вывод R/W (чтение/запись)
#define LCD_ClearBit_RW   PORT_ResetBits(BRD_LCD_RW_PORT, BRD_LCD_RW_PIN)
#define LCD_SetBit_RW     PORT_SetBits  (BRD_LCD_RW_PORT, BRD_LCD_RW_PIN)

// Вывод A0 (команды/данные)
#define LCD_ClearBit_A0   PORT_ResetBits(BRD_LCD_A0_PORT, BRD_LCD_A0_PIN)
#define LCD_SetBit_A0     PORT_SetBits  (BRD_LCD_A0_PORT, BRD_LCD_A0_PIN)

// Вывод E (стробирование данных)
#define LCD_ClearBit_E    PORT_ResetBits(BRD_LCD_E_PORT, BRD_LCD_E_PIN)
#define LCD_SetBit_E      PORT_SetBits  (BRD_LCD_E_PORT, BRD_LCD_E_PIN)


void LCD_ConfigureGPIO(void)
{
  // Инициализировать выводов для работы с дисплеем
  // Структура для инициализации линий ввода-вывода
  PORT_InitTypeDef PortInitStruct;

  // Разрешение тактирования требуемых портов
  RST_CLK_PCLKcmd (BRD_LCD_CLOCK, ENABLE);

  // Общая конфигурация линий ввода-вывода
  PortInitStruct.PORT_PULL_UP   = PORT_PULL_UP_OFF;
  PortInitStruct.PORT_PULL_DOWN = PORT_PULL_DOWN_OFF;
  PortInitStruct.PORT_PD_SHM    = PORT_PD_SHM_OFF;
  PortInitStruct.PORT_PD        = PORT_PD_DRIVER;
  PortInitStruct.PORT_GFEN      = PORT_GFEN_OFF;

  PortInitStruct.PORT_FUNC      = PORT_FUNC_PORT;
  PortInitStruct.PORT_MODE      = PORT_MODE_DIGITAL;
  PortInitStruct.PORT_SPEED     = PORT_SPEED_MAXFAST;  

//---------   IN Pins -----------
  // Конфигурация и инициализация линий двунаправленной шины данных (DB0...DB7)
  PortInitStruct.PORT_OE        = PORT_OE_IN;
  
  PortInitStruct.PORT_Pin       = BRD_LCD_IN_PINS;
  PORT_Init(BRD_LCD_IN_PORT, &PortInitStruct);
  
#ifdef BRD_LCD_IN_PORT_EX1
  PortInitStruct.PORT_Pin       = BRD_LCD_IN_PINS_EX1;
  PORT_Init(BRD_LCD_IN_PORT_EX1, &PortInitStruct);
#endif  

//---------   OUT Pins -----------
  PortInitStruct.PORT_OE        = PORT_OE_OUT;

  // Конфигурация и инициализация линий цифровых выходов (E1, E2, RES, R/W, A0, E)
  PortInitStruct.PORT_Pin       = BRD_LCD_OUT_PINS;
  PORT_Init(BRD_LCD_OUT_PORT, &PortInitStruct);
  
#ifdef BRD_LCD_OUT_PORT_EX1  
  PortInitStruct.PORT_Pin       = BRD_LCD_OUT_PINS_EX1;
  PORT_Init(BRD_LCD_OUT_PORT_EX1, &PortInitStruct);	
#endif
}	

// Инициализация дисплея
void LCD_Initialize (void)
{
	LCD_ConfigureGPIO();

  // Инициализация драйвера дисплея
  // Сброс вывода RES
  LCD_ClearBit_RES;
  LCD_Delay (200);

  // Установка вывода RES
  LCD_SetBit_RES;
  LCD_Delay (5);

  // Ожидание завершения инициализации
  while ((LCD_ReadStatus (1) & 0x90) && (LCD_ReadStatus (2) & 0x90));

  // Ожидание завершения операций и включение кристалла 1
  while (LCD_ReadStatus (1) & 0x80);
  LCD_Enable (1);

  // Ожидание завершения операций и включение кристалла 2
  while (LCD_ReadStatus (2) & 0x80);
  LCD_Enable (2);

  // Очистка памяти дисплея
  LCD_ClearScreen (1);
  LCD_ClearScreen (2);

  // Отображение заголовочных элементов
  LCD_PutString (header, 1);
  LCD_PutImage  (logo, 0, 0, 1, 1);
}

// Задержка
void LCD_Delay (uint32_t value)
{
  volatile int_fast32_t i = value;
  while ((i--) != 0);
}

// Выбор направления шины данных
void LCD_DataBusDirection (uint8_t direction)
{
  // Передача
  if (direction == OUT)
  {
    LCD_CODE_BUS_OUT
//    MDR_PORTA->OE |= 0x003F;
//    MDR_PORTF->OE |= 0x000C;
  }

  // Прием
  else
  {
    LCD_CODE_BUS_IN
//    MDR_PORTA->OE &= 0xFFC0;
//    MDR_PORTF->OE &= 0xFFF3;
  }
}

// Передача информации на шину данных
void LCD_SetDataBits (uint8_t value)
{
  LCD_CODE_WRITE(value)
//  
//  MDR_PORTA->RXTX &= 0xFFC0;
//  MDR_PORTA->RXTX |= (value & 0x3F); 
//  MDR_PORTF->RXTX &= 0xFFF3;
//  MDR_PORTF->RXTX |= ((value >> 4) & 0x0C); 
}

// Возврат выводов в исходное состояние
void LCD_Reset (uint8_t chip)
{
  // Сброс вывода E
  LCD_ClearBit_E;
  LCD_Delay (5);

  // Сброс вывода A0
  LCD_ClearBit_A0;

  // Сброс вывода R/W
  LCD_ClearBit_RW;

  // Восстановление конфигурации шины данных
  LCD_DataBusDirection (IN);

  // Отмена выбора кристалла (сброса вывода E1 или E2)
  if (chip == 1)
    LCD_ClearBit_E1;
  else
    LCD_ClearBit_E2;
}

// Включение дисплея
void LCD_Enable (uint8_t chip)
{
  // Выбор кристалла (установка вывода E1 или E2)
  if (chip == 1)
    LCD_SetBit_E1;
  else
    LCD_SetBit_E2;

  // Сброс вывода А0 (служебные сигналы)
  LCD_ClearBit_A0;

  // Сброс вывода R/W (передача данных)
  LCD_ClearBit_RW;
  LCD_Delay (5);

  // Конфигурация шины данных для передачи
  LCD_DataBusDirection (OUT);

  // Передача данных
  LCD_SetDataBits (0x3F);
  LCD_Delay (5);

  // Активация стробирования данных
  LCD_SetBit_E;
  LCD_Delay (5);

  // Возврат в исходное состояние
  LCD_Reset (chip);
}

// Выключение дисплея
void LCD_Disable (uint8_t chip)
{
  // Выбор кристалла (установка вывода E1 или E2)
  if (chip == 1)
    LCD_SetBit_E1;
  else
    LCD_SetBit_E2;

  // Сброс вывода А0 (служебные сигналы)
  LCD_ClearBit_A0;

  // Сброс вывода R/W (передача данных)
  LCD_ClearBit_RW;
  LCD_Delay (5);

  // Конфигурация шины данных для передачи
  LCD_DataBusDirection (OUT);

  // Передача данных
  LCD_SetDataBits (0x3E);
  LCD_Delay (5);

  // Активация стробирования данных
  LCD_SetBit_E;
  LCD_Delay (5);

  // Возврат в исходное состояние
  LCD_Reset (chip);
}

// Получение статуса операции
uint8_t LCD_ReadStatus (uint8_t chip)
{
  uint8_t data;

  // Выбор кристалла (установка вывода E1 или E2)
  if (chip == 1)
    LCD_SetBit_E1;
  else
    LCD_SetBit_E2;

  // Сброс вывода A0 (служебные сигналы)
  LCD_ClearBit_A0;

  // Установка вывода R/W (прием данных)
  LCD_SetBit_RW;
  LCD_Delay (5);

  // Конфигурация шины данных для приема
  LCD_DataBusDirection (IN);

  // Установка вывода E
  LCD_SetBit_E;
  LCD_Delay (5);

  // Чтение данных
  data = LCD_CODE_READ //(uint8_t)(MDR_PORTA->RXTX & 0x3F) | (uint8_t)((MDR_PORTF->RXTX << 4) & 0xC0);
  LCD_Delay (5);

  // Возврат в исходное состояние
  LCD_Reset (chip);

  return data;
}

// Выбор страницы
void LCD_SetPage (uint8_t chip, uint8_t page)
{
  // Выбор кристалла (установка вывода E1 или E2)
  if (chip == 1)
    LCD_SetBit_E1;
  else
    LCD_SetBit_E2;

  // Сброс вывода А0 (служебные сигналы)
  LCD_ClearBit_A0;

  // Сброс вывода R/W (передача данных)
  LCD_ClearBit_RW;
  LCD_Delay (5);

  // Конфигурация шины данных для передачи
  LCD_DataBusDirection (OUT);

  // Передача данных
  LCD_SetDataBits (0xB8 | page);
  LCD_Delay (5);

  // Активация стробирования данных
  LCD_SetBit_E;
  LCD_Delay (5);

  // Возврат в исходное состояние
  LCD_Reset (chip);
}

// Выбор адреса колонки
void LCD_SetAddress (uint8_t chip, uint8_t address)
{
  // Выбор кристалла (установка вывода E1 или E2)
  if (chip == 1)
    LCD_SetBit_E1;
  else
    LCD_SetBit_E2;

  // Сброс вывода А0 (служебные сигналы)
  LCD_ClearBit_A0;

  // Сброс вывода R/W (передача данных)
  LCD_ClearBit_RW;
  LCD_Delay (5);

  // Конфигурация шины данных для передачи
  LCD_DataBusDirection (OUT);

  // Передача данных
  LCD_SetDataBits (0x40 | address);
  LCD_Delay (5);

  // Активация стробирования данных
  LCD_SetBit_E;
  LCD_Delay (5);

  // Возврат в исходное состояние
  LCD_Reset (chip);
}

// Запись данных в ОЗУ дисплея
void LCD_WriteData (uint8_t chip, uint8_t data)
{
  // Выбор кристалла (установка вывода E1 или E2)
  if (chip == 1)
    LCD_SetBit_E1;
  else
    LCD_SetBit_E2;

  // Установка вывода А0 (сигналы данных)
  LCD_SetBit_A0;

  // Сброс вывода R/W (передача данных)
  LCD_ClearBit_RW;
  LCD_Delay (5);

  // Конфигурация шины данных для передачи
  LCD_DataBusDirection (OUT);

  // Передача данных
  LCD_SetDataBits (data);
  LCD_Delay (5);

  // Активация стробирования данных
  LCD_SetBit_E;
  LCD_Delay (5);

  // Возврат в исходное состояние
  LCD_Reset (chip);
}

// Чтение данных из ОЗУ дисплея
uint8_t LCD_ReadData (uint8_t chip)
{
  uint8_t data = 0;

  // Выбор кристалла (установка вывода E1 или E2)
  if (chip == 1)
    LCD_SetBit_E1;
  else
    LCD_SetBit_E2;

  // Установка вывода А0 (сигналы данных)
  LCD_SetBit_A0;

  // Установка вывода R/W (прием данных)
  LCD_SetBit_RW;
  LCD_Delay (5);

  // Конфигурация шины данных для приема
  LCD_DataBusDirection (IN);

  // Передача данных
  LCD_SetDataBits (data);
  LCD_Delay (5);

  // Активация стробирования данных
  LCD_SetBit_E;
  LCD_Delay (5);

  // Чтение данных
  data = LCD_CODE_READ                      
  LCD_Delay (5);

  // Возврат в исходное состояние
  LCD_Reset (chip);

  return (data);
}

// Очистка страницы
void LCD_ClearPage (uint8_t chip, uint8_t page)
{
  int32_t i;

  // Выбор страницы
  LCD_SetPage (chip, page);

  // Выбор адреса
  LCD_SetAddress (chip, 0x00);

  // Цикл очистки
  for (i = 0; i < 64; i++)
  {
    // Ожидание завершения операций с дисплеем
    while (LCD_ReadStatus (chip) & 0x80);

    // Сброс битов
    LCD_WriteData (chip, 0x00);
  }
}

// Очистка дисплея
void LCD_ClearScreen (uint8_t chip)
{
  int32_t i;

  // Очистка всех страниц
  for (i = 0; i < 8; i++)
  LCD_ClearPage (chip, i);
}

// Вывод символа
void LCD_PutSymbol (uint8_t symbol, int32_t x, int32_t y)
{
  int32_t chip, page, address;
  int32_t i;
  int32_t index;  // Индекс первого элемента символа в массиве шрифта

  chip    = (int32_t)(x / 8) + 1;    // Выражение номера кристалла через координату символа по оси абсцисс
  page    = y;                       // Выражение номера страницы через координату символа по оси ординат
  address = (int32_t)((x % 8) * 8);  // Выражение номера колонки через координату символа по оси абсцисс

  // Выбор страницы
  LCD_SetPage (chip, page);

  // Выбора адреса колонки
  LCD_SetAddress (chip, address);

  // Проверка пренадлежности символа к заданному диапазону кодировок
  if (symbol >= FONT_MIN_CODE && symbol <= FONT_MAX_CODE)
    index = (((uint32_t) symbol) - FONT_MIN_CODE) * 8;

  // Если заданный код находится вне диапазона, то выбирается первый символ массива (пробел)
  else
    index = 0;

  // Вывод символа
  for (i = index; i < (index + 8); i++)
  {
    // Ожидание завершения операций с дисплеем
    while (LCD_ReadStatus (chip) & 0x80);

    // Запись символа в память дисплея
    LCD_WriteData (chip, Font[i]);
  }
}

// Вывод строки
void LCD_PutString (const char* string, int32_t y)
{
  int32_t i;

  // Цикл формирования строки
  for (i = 0; i < LCD_SCREEN_WIDTH; i++)
  {
    // Остановка цикла, если достигнут конец строки
    if (!string[i])
      break;

    // Вывод символа
    LCD_PutSymbol (string[i], i, y);
  }

  // Заполнение оставшейся части массива пустыми символами
  for (; i < LCD_SCREEN_WIDTH; i++)
    LCD_PutSymbol (0x20, i, y);
}

// Горизональное перемещение строки
void LCD_ScrollString (const char* string, int32_t y, int32_t shift)
{
  int32_t i, j;
  int32_t length;                     // Длина исходной строки
  char temp;                          // Переменная для хранения временных данных
  char scroll[LCD_SCREEN_WIDTH + 1];  // Строка, получаемая в результате сдвига

  // Вычисление длины исходной строки
  length = strlen (string);

  // Остановка выполнения функции, если исходная строка пуста
  if (!length)
    return;

  // Центрирование начального положения строки
  shift += (LCD_SCREEN_WIDTH - length) / 2;

  // Привязка значений сдвигового счетчика к ширине дисплея
  shift %= LCD_SCREEN_WIDTH;

  // Цикл сдвига
  for (i = 0; i < LCD_SCREEN_WIDTH; i++)
  {
    // Сдвиг элемента
    j = LCD_SCREEN_WIDTH - shift + i;

    // Если достигнут край дисплея, то элемент перемещается в начало
    if (j >= LCD_SCREEN_WIDTH)
      j %= LCD_SCREEN_WIDTH;

    // Запись сдвинутого элемента в новую строку
    // Если элементов не осталось, то строка заполняется пробелами
    if (j < length)
      temp = string[j];
    else
      temp = 0x20;

    scroll[i] = temp;
  }

  // Вывод сформированной строки на дисплей
  LCD_PutString (scroll, y);
}

// Вывод изображения
void LCD_PutImage (const uint8_t* image, int32_t top, int32_t left, int32_t bottom, int32_t right)
{
  int32_t i, x, y;
  int32_t chip, page, address;
  int32_t count = 0;

  // Циклы формирования изображения
  for (y = top; y <= bottom; y++)
    for (x = left; x <= right; x++)
    {
      chip    = (int32_t)(x / 8) + 1;    // Выражение номера кристалла через координату символа по оси абсцисс
      page    = y;                       // Выражение номера страницы через координату символа по оси ординат
      address = (int32_t)((x % 8) * 8);  // Выражение номера колонки через координату символа по оси абсцисс

      // Выбор страницы
      LCD_SetPage (chip, page);

      // Выбора адреса колонки
      LCD_SetAddress (chip, address);

      // Цикл формирования элемента изображения
      for (i = 0; i < 8; i++)
      {
        // Ожидание завершения операций с дисплеем
        while (LCD_ReadStatus (chip) & 0x80);

        // Запись элемента изображения размером 8x8 в память дисплея
        LCD_WriteData (chip, image[count + i]);
      }

      // Сдвиг на следующую строку
      count += 8;
    }
}
