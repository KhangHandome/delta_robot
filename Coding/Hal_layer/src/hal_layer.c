#include "hal_layer.h"
#include <pigpio.h>
#include <stdio.h>

/**
 * @brief Initialize pigpio library.
 * @return true if successful, false otherwise.
 */
bool HAL_Init(void) {
    if (gpioInitialise() < 0) {
        fprintf(stderr, "pigpio init failed\n");
        return false;
    }
    return true;
}

/**
 * @brief Set GPIO as output.
 * @param[in] gpio GPIO number.
 */
void HAL_SetPinOutput(int gpio) {
    gpioSetMode(gpio, PI_OUTPUT);
}

/**
 * @brief Set GPIO as input.
 * @param[in] gpio GPIO number.
 */
void HAL_SetPinInput(int gpio) {
    gpioSetMode(gpio, PI_INPUT);
}

/**
 * @brief Write HIGH or LOW to GPIO pin.
 * @param[in] gpio GPIO number.
 * @param[in] value true = HIGH, false = LOW.
 */
void HAL_WritePin(int gpio, bool value) {
    gpioWrite(gpio, value ? 1 : 0);
}

/**
 * @brief Read digital level from GPIO pin.
 * @param[in] gpio GPIO number.
 * @return true if HIGH, false if LOW.
 */
bool HAL_ReadPin(int gpio) {
    return gpioRead(gpio);
}

/**
 * @brief Set PWM duty cycle (0–100%).
 * @param[in] gpio GPIO number.
 * @param[in] duty_percent PWM duty in percent.
 */
void HAL_SetPWM(int gpio, float duty_percent) {
    int duty = (int)(duty_percent * 255.0 / 100.0);
    gpioPWM(gpio, duty);
}

/**
 * @brief Set PWM frequency for GPIO.
 * @param[in] gpio GPIO number.
 * @param[in] freq Frequency in Hz.
 */
void HAL_SetPWMFreq(int gpio, unsigned int freq) {
    gpioSetPWMfrequency(gpio, freq);
}

/**
 * @brief Set PWM resolution/range.
 * @param[in] gpio GPIO number.
 * @param[in] range PWM range (e.g., 255).
 */
void HAL_SetPWMRatio(int gpio, int range) {
    gpioSetPWMrange(gpio, range);
}

/**
 * @brief Read encoder GPIO logic state (basic placeholder).
 * @param[in] gpio GPIO number.
 * @return 1 if HIGH, 0 if LOW.
 */
int HAL_ReadEncoderFreq(int gpio) {
    return gpioRead(gpio); // thực chất đọc logic level, chưa đếm xung
}

/**
 * @brief Deinitialize pigpio.
 */
void HAL_Deinit(void) {
    gpioTerminate();
}
