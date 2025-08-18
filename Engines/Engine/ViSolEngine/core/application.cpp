#include "application.h"
#include <spdlog/spdlog.h>

#include <GLFW/glfw3.h>


namespace ViSolEngine
{
    Application::Application(const ApplicationConfiguration &config) : mConfig(config)
    {
        Logger::init();
        CORE_LOG_INFO("Info works");
        CORE_LOG_TRACE("Trace works");
        CORE_LOG_WARN("Warn works");
        CORE_LOG_ERROR("Error works");
        CORE_LOG_CRITICAL("Critical works");
    }

    void Application::run()
    {
        std::cout << "App is running: " << mConfig.Width << ", " << mConfig.Height << ", " << mConfig.Title << std::endl;
    }

}
