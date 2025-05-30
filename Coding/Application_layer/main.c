#include <stdio.h>
#include <unistd.h>     // for sleep()
#include "hal_gpio.h"
#include "hybrid_servo.h"

int main(void) {
    if (!HAL_Init()) {
        printf("Không thể khởi tạo pigpio.\n");
        return 1;
    }

    // Khởi tạo đối tượng servo: GPIO 18 là STEP, GPIO 23 là DIR, 2000 step/vòng
    HybridServo my_servo = {
        .step_pin = 18,
        .dir_pin = 23,
        .steps_per_rev = 2000
    };

    // Thiết lập GPIO output
    HybridServo_Init(&my_servo);

    // --- Cấu hình ---
    float rpm = 60.0f;      // Tốc độ quay (vòng/phút)
    float rev = 2.0f;       // Số vòng cần quay
    float duration_sec = (rev * 60.0f) / rpm;

    // Bắt đầu quay thuận
    printf("Quay %0.1f vòng ở %0.1f RPM...\n", rev, rpm);
    HybridServo_Rotate(&my_servo, rpm, true);  // true = chiều thuận

    // Chờ đủ thời gian quay
    usleep((int)(duration_sec * 1e6));  // chuyển giây -> micro giây

    // Dừng lại
    printf("Dừng.\n");
    HybridServo_Stop(&my_servo);

    // Giải phóng thư viện pigpio
    HAL_Deinit();

    return 0;
}
