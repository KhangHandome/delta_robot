# delta_robot
# Nguyên lý điều khiển của hybrid servo 
- Ta cần cấp 1 xung đầu vào cho hybrid servo, với mỗi xung đầu vào nó sẽ quay 1 góc là 1 / (microstep resolution )
Ví dụ : với cài đặt microstep resolution là 2000, mỗi góc quay sẽ là 1 / 2000 * 360 =  0.18 độ 
Khi cấp 1 xung với tần số 2000hz thì động cơ quay 1 vòng 1 phút, khi cấp 1 xung với 20000 hz thì động cơ sẽ quay 10 vòng 1 phút 
Từ nguyên lý đó ta sẽ code driver điều khiển cho động cơ dùng pwm ( băm xung vuông ) làm xung điều khiển, với các  vi điều khiển khác làm tương tự 
# Cách điều khiển với rasberrypi 
<!-- To install pigpio on rasbery pi you need to uses this command  -->
sudo apt update
sudo apt install pigpio python3-pigpio
<!--Thư viện pigpio yêu cầu chạy một daemon (trình nền) có tên pigpiod.  -->
sudo pigpiod
<!-- Hoặc có thể để tự khởi động mỗi khi bật máy  -->
sudo systemctl enable pigpiod
sudo systemctl start pigpiod
# Hướng dẫn sử dụng thư viện 
## Với chế độ gpio input output 
int gpioSetMode(unsigned gpio, unsigned mode);	Đặt chế độ chân GPIO: PI_INPUT, PI_OUTPUT, PI_ALT0...
int gpioGetMode(unsigned gpio);	Đọc chế độ của chân GPIO
int gpioWrite(unsigned gpio, unsigned level);	Ghi mức logic (0 hoặc 1) ra GPIO
int gpioRead(unsigned gpio);	Đọc trạng thái GPIO (trả về 0 hoặc 1)
## Với chế độ pwm ( tạo xung vuông ) 
int gpioPWM(unsigned gpio, unsigned dutycycle);	Gửi PWM tới chân gpio với chu kỳ công suất từ 0 đến 255
int gpioSetPWMfrequency(unsigned gpio, unsigned frequency);	Thiết lập tần số PWM (Hz)
int gpioGetPWMfrequency(unsigned gpio);	Đọc tần số PWM hiện tại
int gpioSetPWMrange(unsigned gpio, unsigned range);	Thiết lập dải dutycycle (mặc định 255)
## Điều khiển servo 
int gpioServo(unsigned gpio, unsigned pulsewidth);	Gửi xung servo 500–2500μs (micro giây)
int gpioGetServoPulsewidth(unsigned gpio);	Đọc độ rộng xung servo hiện tại
int gpioSetPWMfrequency() + gpioPWM()	Có thể dùng thay thế nếu muốn điều khiển servo kiểu khác
## Ngắt ngoài 
int gpioSetAlertFunc(unsigned gpio, gpioAlertFunc_t f);	Gắn hàm callback cho cả 2 cạnh (rising & falling)
int gpioSetAlertFuncEx(unsigned gpio, gpioAlertFuncEx_t f, void *userdata);	Giống trên, có thêm tham số người dùng
int gpioSetISRFunc(unsigned gpio, unsigned edge, int timeout, gpioISRFunc_t f);	Gắn ngắt theo cạnh: RISING_EDGE, FALLING_EDGE, EITHER_EDGE
int gpioSetISRFuncEx(...)	Phiên bản có thêm userdata
### Kiểu dữ liệu của call back 
typedef void (*gpioAlertFunc_t)(int gpio, int level, uint32_t tick);
# Lưu ý cho việc khởi tạo và kết thúc 
int gpioInitialise(void);	Gọi một lần duy nhất để khởi động thư viện
void gpioTerminate(void);	Dọn dẹp tài nguyên khi kết thúc