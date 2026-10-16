#include "drv_eeprom_at24c.h"

static I2C_HandleTypeDef *l_i2c_instance;

static HAL_StatusTypeDef validate_range(eeprom_at24c_address start_address, uint16_t length)
{
    if (l_i2c_instance == NULL ||
        start_address > MAX_ADDRESS ||
        length > (MAX_ADDRESS - start_address))
    {
        return HAL_ERROR;
    }

    return HAL_OK;
}


HAL_StatusTypeDef drv_eeprom_at24c_init(I2C_HandleTypeDef *i2c_instance)
{
    if (i2c_instance == NULL)
    {
        return HAL_ERROR;
    }

    l_i2c_instance = i2c_instance;
    return HAL_OK;
}

HAL_StatusTypeDef drv_eeprom_at24c_write(eeprom_at24c_address start_address, uint8_t *pData, uint16_t length)
{
    HAL_StatusTypeDef status = validate_range(start_address, length);
    if (status != HAL_OK || (length > 0U && pData == NULL))
    {
        return HAL_ERROR;
    }

    while (length > 0U)
    {
        uint16_t page_offset = start_address % AT24C_PAGE_SIZE;
        uint16_t chunk_length = AT24C_PAGE_SIZE - page_offset;
        if (chunk_length > length)
        {
            chunk_length = length;
        }

        status = HAL_I2C_Mem_Write(l_i2c_instance,  AT24C_ADDRESS, start_address,   I2C_MEMADD_SIZE_16BIT, pData, chunk_length, AT24C_I2C_TIMEOUT);
        if (status != HAL_OK)
        {
            return status;
        }

        // Wait until the device is ready
        while( HAL_I2C_IsDeviceReady(l_i2c_instance, AT24C_ADDRESS, 100U, 1U) != HAL_OK );

        start_address += chunk_length;
        pData += chunk_length;
        length -= chunk_length;
    }

    return HAL_OK;
}

HAL_StatusTypeDef drv_eeprom_at24c_read(eeprom_at24c_address start_address, uint8_t *pData, uint16_t length)
{
    HAL_StatusTypeDef status = validate_range(start_address, length);
    if (status != HAL_OK || (length > 0U && pData == NULL))
    {
        return HAL_ERROR;
    }

    while (length > 0U)
    {
        uint16_t chunk_length = length;
        if (chunk_length > AT24C_PAGE_SIZE)
        {
            chunk_length = AT24C_PAGE_SIZE;
        }

        status = HAL_I2C_Mem_Read(l_i2c_instance,  AT24C_ADDRESS,  start_address,  I2C_MEMADD_SIZE_16BIT,  pData,  chunk_length,  AT24C_I2C_TIMEOUT);
        if (status != HAL_OK)
        {
            return status;
        }
        while( HAL_I2C_IsDeviceReady(l_i2c_instance, AT24C_ADDRESS, 100U, 1U) != HAL_OK );

        start_address += chunk_length;
        pData += chunk_length;
        length -= chunk_length;
    }

    return HAL_OK;
}

HAL_StatusTypeDef drv_eeprom_at24c_erase(eeprom_at24c_address start_address, uint16_t length)
{
    uint8_t erased_data[AT24C_PAGE_SIZE];
    uint16_t i;
    HAL_StatusTypeDef status = validate_range(start_address, length);

    if (status != HAL_OK)
    {
        return status;
    }

    for (i = 0U; i < AT24C_PAGE_SIZE; i++)
    {
        erased_data[i] = 0xFFU;
    }

    while (length > 0U)
    {
        uint16_t page_offset = start_address % AT24C_PAGE_SIZE;
        uint16_t chunk_length = AT24C_PAGE_SIZE - page_offset;

        if (chunk_length > length)
        {
            chunk_length = length;
        }

        status = drv_eeprom_at24c_write(start_address, erased_data, chunk_length);
        if (status != HAL_OK)
        {
            return status;
        }

        start_address += chunk_length;
        length -= chunk_length;
    }

    return HAL_OK;
}

HAL_StatusTypeDef drv_eeprom_at24c_blankcheck(eeprom_at24c_address start_address, uint16_t length)
{
    uint8_t data[AT24C_PAGE_SIZE];
    HAL_StatusTypeDef status;

    status = validate_range(start_address, length);
    if (status != HAL_OK)
    {
        return status;
    }

    while (length > 0U)
    {
        uint16_t chunk_length = length;
        uint16_t i;

        if (chunk_length > AT24C_PAGE_SIZE)
        {
            chunk_length = AT24C_PAGE_SIZE;
        }

        status = drv_eeprom_at24c_read(start_address, data, chunk_length);
        if (status != HAL_OK)
        {
            return status;
        }

        for (i = 0U; i < chunk_length; i++)
        {
            if (data[i] != 0xFFU)
            {
                return HAL_OK;
            }
        }

        start_address += chunk_length;
        length -= chunk_length;
    }

    return HAL_OK;
}
