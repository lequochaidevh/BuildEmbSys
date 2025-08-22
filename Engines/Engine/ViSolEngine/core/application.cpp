#include "application.h"
#include <spdlog/spdlog.h>
#define GLAD_CL_IMPLEMENTATION

#include "window/windowPlatform.h"
#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace ViSolEngine
{
    Application::Application(const ApplicationConfiguration &config) : mConfig(config)
    {
        mNativeWindow.reset(WindowPlatform::create(config.eWindowSpec));
        if (!mNativeWindow->init(config))
        {
            CORE_LOG_CRITICAL("mNativeWindow init failed");
            return;
        }
    }

    void Application::run()
    {
        CORE_LOG_INFO("App is running: {0} {1} {2} ", mConfig.width, mConfig.height, mConfig.title);
        onInitClient();

        while (!mNativeWindow->shouldClose())
        {
            mNativeWindow->swapbuffers();

            mNativeWindow->pollsEvent();
        }

        onShutdownClient();
        //     if (glfwInit())
        //     {
        //         CORE_LOG_INFO("GLFW Init successfully");
        //     }
    }
    void Application::shutdown() {
		mNativeWindow->shutdown();
	}
}
