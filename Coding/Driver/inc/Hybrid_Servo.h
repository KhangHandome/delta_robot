#ifndef HYBRID_SERVO_H
#define HYBRID_SERVO_H

#include <stdbool.h>

/**
 * @brief Struct đại diện cho một động cơ Hybrid Servo.
 */
typedef struct {
    int step_pin;           ///< GPIO chân STEP
    int dir_pin;            ///< GPIO chân DIR
    int steps_per_rev;      ///< Số bước để quay 1 vòng (ví dụ 2000)
} HybridServo;

/**
 * @brief Khởi tạo servo: cấu hình chân output.
 * @param[in,out] servo Con trỏ đến struct servo.
 */
void HybridServo_Init(HybridServo* servo);

/**
 * @brief Quay servo 1 số vòng nhất định với tốc độ (rpm).
 * @param[in] servo Con trỏ servo.
 * @param[in] rpm Tốc độ vòng/phút.
 * @param[in] dir true = chiều thuận, false = ngược.
 */
void HybridServo_Rotate(HybridServo* servo, float rpm, bool dir);

/**
 * @brief Dừng servo (dừng tạo xung).
 * @param[in] servo Con trỏ servo.
 */
void HybridServo_Stop(HybridServo* servo);

#endif // HYBRID_SERVO_H
