# Example Generate Pulse

Ví dụ tạo xung vuông bằng Output Compare của TIM1 trên STM32F103C8T6. Driver cập nhật thời điểm so sánh trong ngắt để tiếp tục đảo trạng thái chân timer, không cần vòng lặp bận trong `main`.

## Phần cứng và công cụ

- MCU: STM32F103C8T6
- IDE: STM32CubeIDE
- HAL/CMSIS: STM32CubeF1
- Timer: TIM1, bộ đếm lên, Output Compare chế độ Toggle
- Các đầu ra được cấu hình:

| Kênh | Chân MCU | Tần số trong ví dụ |
| --- | --- | ---: |
| TIM1_CH1 | PA8 | 10 kHz |
| TIM1_CH2 | PA9 | 5 kHz |
| TIM1_CH3 | PA10 | 1 kHz |
| TIM1_CH4 | PA11 | 1 kHz |

Đầu ra là tín hiệu logic 3,3 V của MCU. Khi nối với driver động cơ hoặc tải khác, cần kiểm tra mức điện áp, dòng điện và yêu cầu giao tiếp của thiết bị đó; không nối tải công suất trực tiếp vào chân MCU.

## Cấu hình timer và tính tần số

Clock cấu hình trong ví dụ giả định HSE 8 MHz:

- PLL x8 tạo SYSCLK 64 MHz.
- AHB chia 2 nên HCLK là 32 MHz.
- APB2 chia 1 nên clock TIM1 là 32 MHz.
- Prescaler TIM1 là 31, do đó tần số đếm của timer là `32 MHz / (31 + 1) = 1 MHz`.

Driver nhận tần số clock timer tính bằng MHz trong `drv_pulse_init()`. Với cấu hình này, truyền `32`.

Ở chế độ Toggle, timer đảo mức đầu ra sau mỗi nửa chu kỳ:

```text
delta_ticks = timer_clock_hz / ((prescaler + 1) * frequency_hz * 2)
frequency_hz = timer_clock_hz / ((prescaler + 1) * delta_ticks * 2)
```

Vì vậy với bộ đếm 1 MHz, tần số 10 kHz cần 50 tick giữa hai lần đảo mức; một chu kỳ đầy đủ gồm 100 tick (100 µs).

## Sử dụng driver

Khởi tạo timer bằng HAL trước, sau đó khởi tạo driver và gọi `drv_pulse_set_period()` cho mỗi kênh cần chạy:

```c
MX_TIM1_Init();

drv_pulse_init(&htim1, 32);
drv_pulse_set_period(TIM_CHANNEL_1, 10000);
drv_pulse_set_period(TIM_CHANNEL_2, 5000);
drv_pulse_set_period(TIM_CHANNEL_3, 1000);
drv_pulse_set_period(TIM_CHANNEL_4, 1000);
```

Tham số thứ hai của `drv_pulse_set_period()` là **tần số Hz**, dù tên hàm sử dụng từ `period`. Ví dụ `10000` có nghĩa là 10 kHz. Sau khi được khởi động, kênh tiếp tục phát xung trong lúc timer và ngắt còn hoạt động.

API được khai báo trong `Core/Inc/drv_pulse.h`:

```c
void drv_pulse_init(TIM_HandleTypeDef *tim_init, uint16_t clock_input);
void drv_pulse_set_period(uint8_t TIM_Channel, uint16_t pulse);
void drv_pulse_deinit(void);
```

Driver sử dụng ngắt `TIM1_CC_IRQn`; vector ngắt phải gọi `HAL_TIM_IRQHandler(&htim1)`. Cấu hình CubeMX hiện tại đã bật ngắt này và cấu hình chân Alternate Function tương ứng.

## Giới hạn cần lưu ý

- Tần số clock truyền cho driver phải khớp clock đầu vào thực tế của timer. Nếu thay đổi cấu hình RCC, hãy tính lại giá trị này.
- `pulse` phải khác 0. Với cấu hình hiện tại, khoảng nửa chu kỳ tính ra phải nằm trong khoảng 1 đến 32767 tick vì driver lưu giá trị tick trong `int16_t`.
- Tần số thực tế có thể sai khác nhỏ do phép chia số nguyên khi quy đổi sang tick.
- `drv_pulse_deinit()` hiện chỉ bỏ tham chiếu tới timer; hãy dừng timer/kênh bằng HAL trước khi gọi nếu cần ngừng phát xung.

## Build và nạp chương trình

1. Mở STM32CubeIDE và import thư mục project có file `.project` hoặc mở `example_generate_pulse.ioc`.
2. Chọn cấu hình Debug hoặc Release, sau đó Build Project.
3. Kết nối board bằng ST-Link, chọn Debug/Run để nạp firmware.
4. Dùng oscilloscope hoặc logic analyzer đo PA8–PA11 để xác nhận tần số và mức logic.

Các thông số clock, timer và chân ngoại vi có thể được xem hoặc chỉnh sửa trong `example_generate_pulse.ioc`.
