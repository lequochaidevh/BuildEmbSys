#include <iostream>
#include "camera_utils.h" // private header, only for internal use
#include "camera_device.h"
namespace modules::camera {

class SimpleCamera : public ICameraDevice {
public:
    SimpleCamera() = default;
    ~SimpleCamera() override = default;

    bool open(const std::string &device) override {
        device_ = device;
        std::cout << "[SimpleCamera] opened device: " << device_ << "\n";
        opened_ = true;
        return true;
    }

    std::string grabFrame() override {
        if (!opened_) return {};
        static int cnt = 0;
        return "frame#" + std::to_string(++cnt) + " from " + device_;
    }

    void close() override {
        if (opened_) {
            std::cout << "[SimpleCamera] closed device: " << device_ << "\n";
            debug_camera_internal(); // Call to internal debug function
            opened_ = false;
            device_.clear();
        }
    }

private:
    bool opened_ = false;
    std::string device_;
};

std::unique_ptr<ICameraDevice> createDefaultCamera() {
    return std::make_unique<SimpleCamera>();
}

} // namespace modules::camera
