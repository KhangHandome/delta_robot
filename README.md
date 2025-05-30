# delta_robot
# Nguyên lý điều khiển của hybrid servo 
- Ta cần cấp 1 xung đầu vào cho hybrid servo, với mỗi xung đầu vào nó sẽ quay 1 góc là 1 / (microstep resolution )
Ví dụ : với cài đặt microstep resolution là 2000, mỗi góc quay sẽ là 1 / 2000 * 360 =  0.18 độ 
Khi cấp 1 xung với tần số 2000hz thì động cơ quay 1 vòng 1 phút, khi cấp 1 xung với 20000 hz thì động cơ sẽ quay 10 vòng 1 phút 
Từ nguyên lý đó ta sẽ code driver điều khiển cho động cơ dùng pwm ( băm xung vuông ) làm xung điều khiển, với các  vi điều khiển khác làm tương tự 