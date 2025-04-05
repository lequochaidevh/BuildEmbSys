#include "../inc/pid_autotune.h"
#include <iostream>
#include <chrono>
#include <thread> // Để sử dụng std::this_thread::sleep_for
#include <cmath>
PID_AutoTune::PID_AutoTune() {
    Kp = 1.0;
    Ki = 0.0;
    Kd = 0.0;
    Ku = 0.0;
    Pu = 0.0;
    setpoint = 0.0;
    previous_error = 0.0;
    integral = 0.0;
    autoTuneMode = true;
}

void PID_AutoTune::begin() {
    // Khởi tạo MPU6050
    Wire.begin();
    mpu.initialize();

    if (!mpu.testConnection()) {
        printf("Không thể kết nối với MPU6050\n");
        while (1);  // Dừng chương trình nếu không kết nối được
    }
}

void PID_AutoTune::autoTune() {
    // Bắt đầu quá trình auto-tuning PID
    Kp = 1.0;  // Giá trị bắt đầu cho Kp
    Ki = 0.0;  // Ki = 0 lúc đầu
    Kd = 0.0;  // Kd = 0 lúc đầu

    bool foundOscillation = false;
    auto lastTime = std::chrono::high_resolution_clock::now();

    unsigned long previousDeltaTime = 0;  // Theo dõi thời gian giữa các vòng lặp
    float lastAngle = 0.0;
    float angleChange = 0.0;

    while (!foundOscillation) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::milliseconds deltaTime = \
                std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime);

        lastTime = currentTime;

        // Lấy dữ liệu từ cảm biến MPU6050
        int16_t ax, ay, az;
        mpu.getAcceleration(&ax, &ay, &az);
        float angle = atan2(ay, az) * 180.0 / 3.14159265;  // Tính góc nghiêng

        // Tính sự thay đổi của góc
        angleChange = std::fabs(angle - lastAngle); ;
        lastAngle = angle;

        // Nếu sự thay đổi góc lớn và liên tục trong một thời gian, xem như hệ thống đang dao động
        if (angleChange > 2.0 && deltaTime.count() > (int64_t)previousDeltaTime) {
            if (!foundOscillation) {
                Ku = Kp;  // Ghi lại giá trị khuếch đại lúc hệ thống bắt đầu dao động
                previousDeltaTime = deltaTime.count();  // Ghi lại chu kỳ dao động
            }
            Pu = deltaTime.count();  // Ghi lại chu kỳ dao động
            foundOscillation = true;  // Kết thúc quá trình tìm kiếm dao động
        }

        // Điều khiển động cơ
        input = angle;
        pidControl(input, deltaTime.count());

        // Điều khiển động cơ
        setMotorSpeed(output);

        // Chờ một khoảng thời gian nhỏ
        std::this_thread::sleep_for(std::chrono::seconds(50));
    }

    // Tính toán giá trị PID theo công thức Ziegler-Nichols
    Kp = 0.6 * Ku;
    Ki = 2 * Kp / Pu;
    Kd = Kp * Pu / 8;

    printf("Auto-tuning complete. PID parameters: ");
    printf("Kp: ");
    printf("%f",Kp);
    printf(", Ki: ");
    printf("%f",Ki);
    printf(", Kd: ");
    printf("%f",Kd);
    printf("\n");
    autoTuneMode = false;  // Tắt chế độ auto-tuning sau khi hoàn tất
}

void PID_AutoTune::pidControl(double input, unsigned long deltaTime) {
    // Tính toán sai số
    double error = setpoint - input;
    integral += error * deltaTime;  // Tích phân của sai số nhân với deltaTime
    double derivative = (error - previous_error) / deltaTime;  // Đạo hàm của sai số

    // Tính toán giá trị điều khiển PID
    output = Kp * error + Ki * integral + Kd * derivative;

    // Cập nhật sai số trước đó
    previous_error = error;
}
////////////////////////////////////////////////////////////
int constrain(int x, int a, int b) {
    return (x < a) ? a : (x > b) ? b : x;
}
void analogWrite(int a, int b) {
    printf("write to pin %d with value: %d\n",a,b);
}
////////////////////////////////////////////////////////////
void PID_AutoTune::setMotorSpeed(double speed) {
    // Giới hạn tốc độ động cơ (giả sử giới hạn từ -255 đến 255)
    int motorSpeed = constrain(speed, -255, 255);

    // Gửi tín hiệu điều khiển động cơ (ở đây bạn sẽ sử dụng PWM hoặc điều khiển tương tự)
    analogWrite(9, motorSpeed);  // Gửi tín hiệu PWM đến chân 9 của Arduino (hoặc điều khiển khác)
}

double PID_AutoTune::getKp() {
    return Kp;
}

double PID_AutoTune::getKi() {
    return Ki;
}

double PID_AutoTune::getKd() {
    return Kd;
}

