#include "Hybrid_Servo.h"
#include "hal_layer.h"
#include <stdio.h>
#include <unistd.h> // for usleep

int main() {
    // Khởi tạo 2 servo
    HybridServo servo1 = {
        .index = 0,
        .step_pin = 17,
        .dir_pin = 27,
        .speed = 0.5f,
        .direction = Clockwise,
        .servo_state = SERVO_STATE_UNINITIALIZED
    };

    HybridServo servo2 = {
        .index = 1,
        .step_pin = 22,
        .dir_pin = 23,
        .speed = 0.8f,
        .direction = CounterClockwise,
        .servo_state = SERVO_STATE_UNINITIALIZED
    };

    // Gọi hàm Init để đăng ký 2 servo vào hệ thống
    HybridServo_Init(&servo1);
    HybridServo_Init(&servo2);

    // Cấu hình thông số cho servo trước khi chạy
    HybridServo_SetUp(&servo1);
    HybridServo_SetUp(&servo2);

    // Bắt đầu chạy servo
    HybridServo_Running();

    // Cho servo chạy trong 3 giây
    usleep(3000000); // 3,000,000 microseconds = 3 seconds

    // Dừng cả 2 servo
    HybridServo_Stop(&servo1);
    HybridServo_Stop(&servo2);

    // In trạng thái kết thúc
    printf("Servo 1 state: %d\n", myHybridServo[0].servo_state);
    printf("Servo 2 state: %d\n", myHybridServo[1].servo_state);

    return 0;
}
