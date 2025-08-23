#pragma once
#include <iostream>
#include <pch.h>
#include "spdlog/spdlog.h"
#include "logger/logger.h"
#include "window/window.h"
#include"core/event/eventDispatcher.h"

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
	private:
		ApplicationConfiguration mConfig;
		Unique<NativeWindow> mNativeWindow;
		EventDispatcher mEventDispatcher;
	};

	extern Application* createApplication();
}
