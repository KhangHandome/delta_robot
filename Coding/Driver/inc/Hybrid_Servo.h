#ifndef _HYBRID_SERVO_H_
#define _HYBRID_SERVO_H_

#include <stdbool.h>
#include <stdint.h>
// Drive support 4 step motor in runtime 
#define MAX_SERVO_INSTANCE 4
typedef enum
{
    Clockwise,
    Counterclockwise,
} Direction_t ; 
/**
 * @brief Trạng thái của servo trong vòng đời điều khiển.
 */
typedef enum
{
    SERVO_STATE_UNINITIALIZED, ///< Chưa khởi tạo
    SERVO_STATE_INITIALIZING,  ///< Đang khởi tạo phần cứng (HAL/pigpio)
    SERVO_STATE_CONFIGURING,   ///< Đang cấu hình thông số PWM, chiều quay,...
    SERVO_STATE_READY,         ///< Đã sẵn sàng hoạt động
    SERVO_STATE_ACTIVE,        ///< Đang điều khiển/gửi xung liên tục
    SERVO_STATE_STOP          ///<  Stop (nếu muốn mở rộng)
} ServoState_t;
/**
 * @brief Struct đại diện cho một động cơ Hybrid Servo.
 */
typedef struct {
    uint8_t      index ;
    uint8_t      step_pin;           ///< GPIO chân STEP
    uint8_t      dir_pin;            ///< GPIO chân DIR
    uint16_t     speed  ;            // Speed of the step motor  
    Direction_t  direction ;         // Set the direction of the stepmotor 
    uint8_t      encoder_pin;        // The encoder pin to  read the encoder of the step motor 
    ServoState_t servo_state;     
} HybridServo;

/**
 * @brief Khởi tạo servo: cấu hình chân output.
 * @param[in,out] servo Con trỏ đến struct servo.
 */

extern void HybridServo_Init(HybridServo* servo);

/**
 * @brief Quay servo 1 số vòng nhất định với tốc độ (rpm).
 * @param[in] servo Con trỏ servo.
 * @param[in] rpm Tốc độ vòng/phút.
 * @param[in] dir true = chiều thuận, false = ngược.
 */
extern void HybridServo_SetUp(HybridServo* servo);

/**
 * @brief Running servo 
 * @param[in] : none 
 */
extern void HybridServo_Running(void);

/**
 * @brief Dừng servo (dừng tạo xung).
 * @param[in] servo Con trỏ servo.
 */
extern void HybridServo_Stop(HybridServo* servo);

#endif // HYBRID_SERVO_H
