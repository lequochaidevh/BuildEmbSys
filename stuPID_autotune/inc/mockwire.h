#ifndef MOCKWIRE_H
#define MOCKWIRE_H
#include <iostream>
#include <cstdio>

class MockWire {
public:
    void begin() {
        // Giả lập việc bắt đầu kết nối I2C
        printf("Wire.begin() called (mock). \n");
    }

    void beginTransmission(uint8_t address) {
        // Giả lập việc bắt đầu truyền dữ liệu I2C
        printf("Wire.beginTransmission(");
        printf("%d", address);
        printf(") called (mock).\n");
    }

    void write(uint8_t value) {
        // Giả lập việc ghi dữ liệu vào I2C
        printf("Wire.write(");
        printf("%d", value);
        printf(") called (mock). \n");
    }

    void endTransmission() {
        // Giả lập việc kết thúc truyền dữ liệu
        printf("Wire.endTransmission() called (mock). \n");
    }
};

extern MockWire Wire;  // Khai báo một đối tượng Wire giả lập

#endif
