#ifndef EEPROM_Test_h
#define EEPROM_Test_h

#include <stdint.h>

typedef enum {
  ST_OK, ST_CLR_ERR, ST_WR_RD_ERR
} EEPROM_TST_STATUS;

EEPROM_TST_STATUS EEPROM_Test_WR_RD (int32_t testPage);

#endif // EEPROM_Test_h
