#ifndef MOCKWIRE_H
#define MOCKWIRE_H

class MockWire {
public:
    void begin() {
        // Giả lập việc bắt đầu kết nối I2C
        Serial.println("Wire.begin() called (mock).");
    }

    void beginTransmission(uint8_t address) {
        // Giả lập việc bắt đầu truyền dữ liệu I2C
        Serial.print("Wire.beginTransmission(");
        Serial.print(address);
        Serial.println(") called (mock).");
    }

    void write(uint8_t value) {
        // Giả lập việc ghi dữ liệu vào I2C
        Serial.print("Wire.write(");
        Serial.print(value);
        Serial.println(") called (mock).");
    }

    void endTransmission() {
        // Giả lập việc kết thúc truyền dữ liệu
        Serial.println("Wire.endTransmission() called (mock).");
    }
};

extern MockWire Wire;  // Khai báo một đối tượng Wire giả lập

#endif
