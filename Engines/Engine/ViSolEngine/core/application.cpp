#include "application.h"
#include <spdlog/spdlog.h>
#define GLAD_CL_IMPLEMENTATION

#include "window/windowPlatform.h"
#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace ViSolEngine
{
    Application::Application(const ApplicationConfiguration &config) : 
        mConfig(config) , mEventDispatcher()
    {
        mNativeWindow.reset(WindowPlatform::create(config.eWindowSpec));
    }

    bool Application::init() {
		
		if (!mNativeWindow->init(mConfig, &mEventDispatcher)) {
			CORE_LOG_CRITICAL("Window spec created failed");
			return false;
		}

		mEventDispatcher.addEventListener<WindowResizedEvent>(BIND_EVENT_FUNCTION(onWindowResizedEvent));

		return true;
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
    }

    void Application::shutdown() {
		mNativeWindow->shutdown();
	}

    bool Application::onWindowResizedEvent(const WindowResizedEvent& windowResizedEvent) {
        CORE_LOG_TRACE("Window resize --- width: {} --- height: {}",
               windowResizedEvent.getWidth(),
               windowResizedEvent.getHeight());
        return true;
    }

}
