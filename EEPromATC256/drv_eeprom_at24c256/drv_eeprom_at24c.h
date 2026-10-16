#ifdef __cplus_plus_
extern "C" {
#endif
#ifndef _DRV_EEPROM_AT_24C_H_
#define _DRV_EEPROM_AT_24C_H_

#define MAX_ADDRESS 0x8000

#include <stdint.h>
typedef uint16_t eeprom_at24c_address;
extern void drv_eeprom_at24c_init();
extern void drv_eeprom_at24c_write(eeprom_at24c_address start_address, uint8_t* pData, uint16_t lenght);
extern void drv_eeprom_at24c_read(eeprom_at24c_address start_address, uitn8_t* pData, uint16_t length);
extern void drv_eeprom_at24c_earse(eeprom_at24c_address start_address, uint16_t length);
extern BOOL drv_eeprom_at24c_blankcheck(eeprom_at24c_address start_address, uint16_t length);

#endif 

#ifdef __cplus_plus_
extern "C" }
#endif