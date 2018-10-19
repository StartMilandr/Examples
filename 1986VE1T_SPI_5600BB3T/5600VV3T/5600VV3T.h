#ifndef __U_5600VV3T_H
#define __U_5600VV3T_H

#include <stdint.h>
#include "brdSPI.h"

/* Выбор контроллера SPI для обмена данными с 5600ВВ3Т */
#define pBRD_SPIx pBRD_SPI1
//#define pBRD_SPIx pBRD_SPI2

/* Параметры функции чтения/записи регистра */
#define READ (uint8_t) 0x00
#define WRITE (uint8_t) 0x01
#define NO_DATA (uint8_t) 0x00

/* Адреса регистров мсх 5600ВВ3Т */
#define CONTROL (uint8_t) 0x01
#define STATUS (uint8_t) 0x02
#define FD_MODE5 (uint8_t) 0x03
#define PHY_MODES_12 (uint8_t) 0x04
#define PHY_MODES_34 (uint8_t) 0x0B

#define RAM_DATA1 (uint8_t) 0x13
#define RAM_DATA2 (uint8_t) 0x14
#define RAM_DATA3 (uint8_t) 0x15
#define RAM_DATA4 (uint8_t) 0x16
#define RAM_DATA5 (uint8_t) 0x17
#define RAM_DATA6 (uint8_t) 0x18
#define RAM_DATA7 (uint8_t) 0x19
#define RAM_DATA8 (uint8_t) 0x1A

#define RAM_CONTROL_0 (uint8_t) 0x1B
#define RAM_CONTROL_1 (uint8_t) 0x1C
#define AGE_CONTROL_0 (uint8_t) 0x1D
#define AGE_CONTROL_1 (uint8_t) 0x1E
#define AGE_CONTROL_2 (uint8_t) 0x1F
#define MAC_RAM_WE_en (uint8_t) 0x20

#define PN1_mask_AND (uint8_t) 0x21
#define PN2_mask_AND (uint8_t) 0x22
#define PN3_mask_AND (uint8_t) 0x23
#define PN4_mask_AND (uint8_t) 0x24
#define PN5_mask_AND (uint8_t) 0x25

#define PN1_mask_OR (uint8_t) 0x26
#define PN2_mask_OR (uint8_t) 0x27
#define PN3_mask_OR (uint8_t) 0x28
#define PN4_mask_OR (uint8_t) 0x29
#define PN5_mask_OR (uint8_t) 0x2A

#define IPG_h (uint8_t) 0x2B
#define IPG_l (uint8_t) 0x2C
#define MAC_TX_CTRL (uint8_t) 0x2D
#define CollWindow (uint8_t) 0x2E
#define MAC_RX_CTRL (uint8_t) 0x2F

#define MinFrame_h (uint8_t) 0x30
#define MinFrame_l (uint8_t) 0x31
#define MaxFrame_h (uint8_t) 0x32
#define MaxFrame_l (uint8_t) 0x33

typedef struct                 // Структура для хранения записи из таблицы MAC-адресов 
{
	union {
		uint64_t data;
		struct {
		  uint64_t MAC : 48;       // Содержит MAC адрес устройства
			uint64_t OLD_CNT : 12;   // Счётчик старения
			uint64_t VALID : 1;      // Флаг активности записанной строки
			uint64_t PORT_NUM : 3;	 // Номер порта, к которому подключено устройство соответствующим MAC-адресом
		};
	};
} MAC_StringTypeDef; 


uint8_t TXRX_Data(BRD_SPI_Obj* BRD_SPI, uint8_t addr, uint8_t rw, uint8_t data); // Запись/чтение внутреннего регистра мсх 5600ВВ3Т
uint16_t Get_Addr(MAC_StringTypeDef MAC_String, uint8_t NCell);                  // Вычисление адреса строки в MAC-таблице на основании его MAC адреса (HASH функции) и выбранной ячейки (0-7)


// Функции для работы с таблицей MAC-адресов, в которых реализована побайтовая перестановка MAC адреса.
// Например в структуре указан MAC=0x123456789ABC, в 5600ВВ3Т будет записан MAC=0xBC9A78563412 (вызвано архитектурными особенностями).

void Read_MAC_Table(BRD_SPI_Obj* BRD_SPI, MAC_StringTypeDef* MAC_String);                  // Чтение всей таблицы MAC-адресов с записью в структуру MAC_StringTypeDef
void Read_MAC_String(BRD_SPI_Obj* BRD_SPI, uint16_t addr, MAC_StringTypeDef* MAC_String);  // Чтение таблицы MAC-адресов по выбранному адресу с записью в структуру MAC_StringTypeDef
void Write_MAC_String(BRD_SPI_Obj* BRD_SPI, uint16_t addr, MAC_StringTypeDef* MAC_String); // Запись структуры MAC_StringTypeDef в таблицу MAC-адресов по выбранному адресу

// Функции для работы с таблицей MAC-адресов, в которых НЕ реализована побайтовая перестановка MAC адреса. MAC адрес считывается и записывается в 5600ВВ3Т как указан в структуре
// Например в структуре указан MAC=0x123456789ABC, в 5600ВВ3Т будет записан MAC=0x123456789ABC.

void Read_MAC_Table_1(BRD_SPI_Obj* BRD_SPI, MAC_StringTypeDef* MAC_String);
void Read_MAC_String_1(BRD_SPI_Obj* BRD_SPI, uint16_t addr, MAC_StringTypeDef* MAC_String);
void Write_MAC_String_1(BRD_SPI_Obj* BRD_SPI, uint16_t addr, MAC_StringTypeDef* MAC_String);


#endif //5600VV3T_H
