#ifndef MOCKMPU6050_H
#define MOCKMPU6050_H

#include <iostream>
#include <cstdio>
class MockMPU6050 {
public:
    void initialize() {
        // Giả lập việc khởi tạo MPU6050
        printf("MPU6050.initialize() called (mock).\n");
    }

    bool testConnection() {
        // Giả lập kiểm tra kết nối của MPU6050 (luôn trả về true)
        printf("MPU6050.testConnection() called (mock).\n");
        return true;
    }

    void getAcceleration(int16_t* ax, int16_t* ay, int16_t* az) {
        // Giả lập việc lấy giá trị gia tốc (giả sử giá trị gia tốc là 0)
        *ax = 0;
        *ay = 0;
        *az = 1000;  // Gia tốc theo chiều z = 1g (1000 mg)
        printf("MPU6050.getAcceleration() called (mock).\n");
    }
};

extern MockMPU6050 mpu;  // Khai báo đối tượng MPU6050 giả lập

#endif
