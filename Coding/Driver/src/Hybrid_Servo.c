#include "hybrid_servo.h"
#include "hal_gpio.h"
#include <unistd.h> // for usleep

void HybridServo_Init(HybridServo* servo) {
    HAL_SetPinOutput(servo->step_pin);
    HAL_SetPinOutput(servo->dir_pin);
}

void HybridServo_Rotate(HybridServo* servo, float rpm, bool dir) {
    unsigned int freq;
    float duration_sec;
    unsigned int duration_us;

    // Set hướng quay
    HAL_WritePin(servo->dir_pin, dir);

    // Tính tần số và thời gian quay
    freq = (unsigned int)(servo->steps_per_rev * rpm / 60.0f);

    // Cấu hình PWM
    HAL_SetPWMFreq(servo->step_pin, freq);
    HAL_SetPWM(servo->step_pin, 50.0f);  // duty 50%
}

void HybridServo_Stop(HybridServo* servo) {
    HAL_SetPWM(servo->step_pin, 0.0f);
}
