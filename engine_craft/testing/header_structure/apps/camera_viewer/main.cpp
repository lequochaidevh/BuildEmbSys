#include "camera_device.h"
#include <iostream>
#include <thread>
#include <chrono>
// #include "camera_utils.h" // Error: private header, only for internal use

int main() {
    auto cam = modules::camera::createDefaultCamera();
    if (!cam->open("/dev/video0")) {
        std::cerr << "Cannot open camera\n";
        return 1;
    }

    for (int i = 0; i < 5; ++i) {
        std::string frame = cam->grabFrame();
        std::cout << "Got: " << frame << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }

    cam->close();
    return 0;
}
