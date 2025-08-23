#pragma once
#include <iostream>
#include <pch.h>
#include "spdlog/spdlog.h"
#include "logger/logger.h"
#include "window/window.h"
#include "window/windowPlatform.h"
#include"core/event/eventDispatcher.h"
#include"core/input/inputState.h"
namespace ViSolEngine {
	struct VISOL_API ApplicationConfiguration {
		uint16_t width, height;
		const char* title;
		EWindowPlatformSpec eWindowSpec;
	};

	class VISOL_API Application {
	public:
		virtual ~Application() = default;
		virtual bool init();
		virtual bool onInitClient() = 0;
		void run();
		virtual void onShutdownClient() = 0;
		virtual void shutdown();
	protected:
		Application() = default;
		Application(const ApplicationConfiguration&);
	private:
		bool onWindowResizedEvent(const WindowResizedEvent&);
		bool onKeyPressedEvent(const KeyPressedEvent&);
		bool onKeyHeldEvent(const KeyHeldEvent&);
		bool onKeyReleasedEvent(const KeyReleasedEvent&);
		bool onMouseMovedEvent(const MouseMovedEvent&);
		bool onMouseScrolledEvent(const MouseScrolledEvent&);
		bool onMouseButtonPressedEvent(const MouseButtonPressedEvent&);
		bool onMouseButtonHeldEvent(const MouseButtonHeldEvent&);
		bool onMouseButtonReleasedEvent(const MouseButtonReleasedEvent&);
	private:
		ApplicationConfiguration mConfig;
		Unique<NativeWindow> mNativeWindow;
		EventDispatcher mEventDispatcher;
		/*new input state*/
		class InputState* mInputState;
	};

	extern Application* createApplication();
}
