#ifndef HAL_GPIO_H
#define HAL_GPIO_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Initialize pigpio library.
 * @return true if initialization successful, false otherwise.
 */
bool HAL_Init(void);

/**
 * @brief Set GPIO pin as output.
 * @param[in] gpio GPIO pin number.
 */
void HAL_SetPinOutput(int gpio);

/**
 * @brief Set GPIO pin as input.
 * @param[in] gpio GPIO pin number.
 */
void HAL_SetPinInput(int gpio);

/**
 * @brief Write digital value to GPIO pin.
 * @param[in] gpio GPIO pin number.
 * @param[in] value true = HIGH, false = LOW.
 */
void HAL_WritePin(int gpio, bool value);

/**
 * @brief Read digital value from GPIO pin.
 * @param[in] gpio GPIO pin number.
 * @return true if HIGH, false if LOW.
 */
bool HAL_ReadPin(int gpio);

/**
 * @brief Set PWM duty cycle for a GPIO pin.
 * @param[in] gpio GPIO pin number.
 * @param[in] duty_percent Duty cycle in percentage (0.0 to 100.0).
 */
void HAL_SetPWM(int gpio, float duty_percent);

/**
 * @brief Set PWM frequency for a GPIO pin.
 * @param[in] gpio GPIO pin number.
 * @param[in] freq Frequency in Hz.
 */
void HAL_SetPWMFreq(int gpio, unsigned int freq);

/**
 * @brief Set PWM range/resolution for a GPIO pin.
 * @param[in] gpio GPIO pin number.
 * @param[in] range PWM range (e.g., 255).
 */
void HAL_SetPWMRatio(int gpio, int range);

/**
 * @brief Read current logic state from encoder GPIO pin.
 *        (Placeholder - encoder implementation can be extended)
 * @param[in] gpio GPIO pin number.
 * @return 1 if high, 0 if low.
 */
int HAL_ReadEncoderFreq(int gpio);

/**
 * @brief Deinitialize pigpio library.
 */
void HAL_Deinit(void);

#endif // HAL_GPIO_H
