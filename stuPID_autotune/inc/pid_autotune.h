#ifndef PID_AUTOTUNE_H
#define PID_AUTOTUNE_H

#include "../inc/mockwire.h"
#include "../inc/mockmpu6050.h"

class PID_AutoTune {
public:
    PID_AutoTune();  // Constructor
    void begin();  // Khởi tạo cảm biến MPU6050
    void autoTune();  // Phương thức tự động điều chỉnh PID
    double getKp();  // Lấy giá trị Kp
    double getKi();  // Lấy giá trị Ki
    double getKd();  // Lấy giá trị Kd

    void setMotorSpeed(double speed);  // Hàm điều khiển động cơ

private:
    MockMPU6050 mpu;  // Đối tượng MPU6050
    double Kp, Ki, Kd;  // Các tham số PID
    double Ku, Pu;  // Các tham số cần thiết cho auto-tuning
    double setpoint;  // Giá trị góc nghiêng mong muốn
    double input, output;  // Đầu vào (góc nghiêng), đầu ra (tốc độ động cơ)
    double previous_error, integral;  // Các giá trị PID
    bool autoTuneMode;  // Cờ kiểm tra chế độ auto-tuning

    void pidControl(double input, unsigned long deltaTime);  // Phương thức tính toán PID
};

#endif
