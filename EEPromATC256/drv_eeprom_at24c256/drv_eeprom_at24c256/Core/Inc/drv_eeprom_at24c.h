#ifndef DRV_EEPROM_AT24C_H
#define DRV_EEPROM_AT24C_H

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_ADDRESS 0x8000U
#define AT24C_ADDRESS 0xA0U
#define AT24C_PAGE_SIZE 64U
#define AT24C_I2C_TIMEOUT 100U
#define TRUE 1U
#define FALSE 0U

typedef uint16_t eeprom_at24c_address;

HAL_StatusTypeDef drv_eeprom_at24c_init(I2C_HandleTypeDef *i2c_instance);
HAL_StatusTypeDef drv_eeprom_at24c_write(eeprom_at24c_address start_address, uint8_t *pData, uint16_t length);
HAL_StatusTypeDef drv_eeprom_at24c_read(eeprom_at24c_address start_address,uint8_t *pData, uint16_t length);
HAL_StatusTypeDef drv_eeprom_at24c_erase(eeprom_at24c_address start_address, uint16_t length);
HAL_StatusTypeDef drv_eeprom_at24c_blankcheck(eeprom_at24c_address start_address,uint16_t length);

#ifdef __cplusplus
}
#endif

#endif
