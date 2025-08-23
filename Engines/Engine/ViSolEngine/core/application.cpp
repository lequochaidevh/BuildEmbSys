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
        /*set new heap --- Set value mInputState*/
        mInputState = mNativeWindow->getInputState();
		mEventDispatcher.addEventListener<KeyPressedEvent>(BIND_EVENT_FUNCTION(onKeyPressedEvent));
        mEventDispatcher.addEventListener<KeyHeldEvent>(BIND_EVENT_FUNCTION(onKeyHeldEvent));
		mEventDispatcher.addEventListener<KeyReleasedEvent>(BIND_EVENT_FUNCTION(onKeyReleasedEvent));
		mEventDispatcher.addEventListener<MouseMovedEvent>(BIND_EVENT_FUNCTION(onMouseMovedEvent));
		mEventDispatcher.addEventListener<MouseScrolledEvent>(BIND_EVENT_FUNCTION(onMouseScrolledEvent));
		mEventDispatcher.addEventListener<MouseButtonPressedEvent>(BIND_EVENT_FUNCTION(onMouseButtonPressedEvent));
		mEventDispatcher.addEventListener<MouseButtonHeldEvent>(BIND_EVENT_FUNCTION(onMouseButtonHeldEvent));
		mEventDispatcher.addEventListener<MouseButtonReleasedEvent>(BIND_EVENT_FUNCTION(onMouseButtonReleasedEvent));

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

    bool Application::onKeyPressedEvent(const KeyPressedEvent& eventContext) {
		CORE_LOG_TRACE("Key {} is pressed", (char)eventContext.getKeyCode());
		return false;
	}

	bool Application::onKeyHeldEvent(const KeyHeldEvent& eventContext) {
		CORE_LOG_TRACE("Key {} is held", (char)eventContext.getKeyCode());
		return false;
	}

	bool Application::onKeyReleasedEvent(const KeyReleasedEvent& eventContext) {
		CORE_LOG_TRACE("Key {} is released", (char)eventContext.getKeyCode());
		return false;
	}

	bool Application::onMouseMovedEvent(const MouseMovedEvent& eventContext) {
		CORE_LOG_TRACE("Mouse position: {}, {}. Mouse relative: {}, {}", eventContext.getPositionX(), eventContext.getPositionY(), eventContext.getOffsetX(), eventContext.getOffsetY());
		return false;
	}

	bool Application::onMouseScrolledEvent(const MouseScrolledEvent& eventContext) {
		CORE_LOG_TRACE("Mouse scroll X: {}, Mouse Scroll Y: {}", eventContext.getScrollX(), eventContext.getScrollY());
		return false;
	}

	bool Application::onMouseButtonPressedEvent(const MouseButtonPressedEvent& eventContext) {
		CORE_LOG_TRACE("Mouse button {} is pressed", eventContext.getButton());
		return false;
	}

	bool Application::onMouseButtonHeldEvent(const MouseButtonHeldEvent& eventContext) {
		CORE_LOG_TRACE("Mouse button {} is held", eventContext.getButton());
		return false;
	}

	bool Application::onMouseButtonReleasedEvent(const MouseButtonReleasedEvent& eventContext) {
		CORE_LOG_TRACE("Mouse button {} is released", eventContext.getButton());
		return false;
	}

}
