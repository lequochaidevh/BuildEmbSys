#include <Wire.h>
#include <MPU6050.h>

// Định nghĩa các tham số PID
double Kp = 1.0;
double Ki = 0.5;
double Kd = 0.1;

double setpoint = 0.0;  // Góc nghiêng mong muốn (0 độ)
double input, output;   // Giá trị đầu vào (góc nghiêng), đầu ra (tốc độ động cơ)

double previous_error = 0.0;
double integral = 0.0;

MPU6050 mpu;

// Các tham số auto-tuning
double Ku = 0.0;  // Hệ số khuếch đại lúc hệ thống dao động đều
double Pu = 0.0;  // Chu kỳ dao động đều
bool autoTuneMode = true;  // Bật chế độ auto-tuning

void setup() {
  // Khởi tạo I2C và cảm biến MPU6050
  Wire.begin();
  mpu.initialize();

  // Kiểm tra kết nối cảm biến
  if (!mpu.testConnection()) {
    Serial.println("Không thể kết nối với MPU6050");
    while (1);
  }

  Serial.begin(9600);
}

double pidControl(double input, unsigned long deltaTime) {
  // Tính toán sai số
  double error = setpoint - input;
  integral += error * deltaTime;  // Tích phân của sai số nhân với deltaTime
  double derivative = (error - previous_error) / deltaTime;  // Đạo hàm của sai số

  // Tính toán giá trị điều khiển PID
  output = Kp * error + Ki * integral + Kd * derivative;

  // Cập nhật sai số trước đó
  previous_error = error;

  return output;
}

void autoTune() {
  // Tự động điều chỉnh tham số PID bằng phương pháp Ziegler-Nichols

  // Bắt đầu thử nghiệm với các giá trị PID ban đầu
  Kp = 1.0;  // Giá trị bắt đầu cho Kp
  Ki = 0.0;  // Ki = 0 lúc đầu
  Kd = 0.0;  // Kd = 0 lúc đầu

  // Quá trình tìm kiếm khuếch đại Ku và chu kỳ dao động Pu
  bool foundOscillation = false;
  unsigned long lastTime = millis();

  while (!foundOscillation) {
    unsigned long currentTime = millis();
    unsigned long deltaTime = currentTime - lastTime;
    lastTime = currentTime;

    // Lấy dữ liệu từ cảm biến MPU6050
    int16_t ax, ay, az;
    mpu.getAcceleration(&ax, &ay, &az);
    float angle = atan2(ay, az) * 180.0 / 3.14159265;  // Tính góc nghiêng

    // Điều khiển PID
    input = angle;
    output = pidControl(input, deltaTime);

    // Nếu hệ thống bắt đầu dao động đều (theo nhận diện bằng sự thay đổi lớn trong giá trị góc)
    if (abs(output) > 5.0) {  // Kiểm tra nếu giá trị đầu ra dao động quá lớn
      if (!foundOscillation) {
        Ku = Kp;  // Ghi lại giá trị khuếch đại lúc hệ thống bắt đầu dao động
      }
      Pu = deltaTime;  // Ghi lại chu kỳ dao động
      foundOscillation = true;  // Kết thúc quá trình tìm kiếm dao động
    }

    // Điều khiển động cơ
    setMotorSpeed(output);

    // Chờ một khoảng thời gian nhỏ
    delay(50);
  }

  // Tính toán giá trị PID theo công thức Ziegler-Nichols
  Kp = 0.6 * Ku;
  Ki = 2 * Kp / Pu;
  Kd = Kp * Pu / 8;

  Serial.print("Auto-tuning complete. PID parameters: ");
  Serial.print("Kp: ");
  Serial.print(Kp);
  Serial.print(", Ki: ");
  Serial.print(Ki);
  Serial.print(", Kd: ");
  Serial.println(Kd);

  autoTuneMode = false;  // Tắt chế độ auto-tuning sau khi hoàn tất
}

void loop() {
  if (autoTuneMode) {
    autoTune();  // Gọi hàm auto-tuning
  } else {
    // Lấy dữ liệu từ cảm biến MPU6050
    int16_t ax, ay, az;
    mpu.getAcceleration(&ax, &ay, &az);
    float angle = atan2(ay, az) * 180.0 / 3.14159265;  // Tính góc nghiêng

    // In giá trị góc lên màn hình Serial
    Serial.print("Góc nghiêng: ");
    Serial.println(angle);

    // Áp dụng thuật toán PID để điều khiển động cơ
    input = angle;
    unsigned long currentTime = millis();
    unsigned long deltaTime = currentTime - lastTime;
    output = pidControl(input, deltaTime);

    // Điều khiển tốc độ động cơ
    setMotorSpeed(output);

    // Cập nhật thời gian
    lastTime = currentTime;
  }
}

// Hàm điều khiển tốc độ động cơ (ví dụ giả định)
void setMotorSpeed(double speed) {
  // Giới hạn tốc độ động cơ (giả sử giới hạn từ -255 đến 255)
  int motorSpeed = constrain(speed, -255, 255);

  // Gửi tín hiệu điều khiển động cơ (ở đây bạn sẽ sử dụng PWM hoặc điều khiển tương tự)
  analogWrite(9, motorSpeed);  // Gửi tín hiệu PWM đến chân 9 của Arduino (hoặc điều khiển khác)
}
