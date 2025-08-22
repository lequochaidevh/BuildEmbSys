#pragma once
#include <iostream>
#include <pch.h>
#include "spdlog/spdlog.h"
#include "logger/logger.h"
#include "window/window.h"

namespace ViSolEngine {
	struct VISOL_API ApplicationConfiguration {
		uint16_t width, height;
		const char* title;
		EWindowPlatformSpec eWindowSpec;
	};

	class VISOL_API Application {
	public:
		virtual ~Application() = default;
		virtual bool init() { return true; }
		virtual bool onInitClient() = 0;
		void run();
		virtual void onShutdownClient() = 0;
		virtual void shutdown();
	protected:
		Application() = default;
		Application(const ApplicationConfiguration&);
	private:
		ApplicationConfiguration mConfig;
		Unique<NativeWindow> mNativeWindow;
	};

	extern Application* createApplication();
}
