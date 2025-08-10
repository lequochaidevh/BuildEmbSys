#pragma once
#include <string>
#include <memory>

// Public API for the camera module
// Send only the declarations (interface) — Not include much impl detail.
namespace modules::camera
{

    class ICameraDevice
    {
    public:
        virtual ~ICameraDevice() = default;
        virtual bool open(const std::string &device) = 0;
        virtual std::string grabFrame() = 0;
        virtual void close() = 0;
    };

    // Factory function to create a default camera device instance
    std::unique_ptr<ICameraDevice> createDefaultCamera();

} // namespace modules::camera
