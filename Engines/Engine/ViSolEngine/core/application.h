#pragma once
#include<iostream>
#include <pch.h>
#include "spdlog/spdlog.h"
#include "logger/logger.h"

namespace ViSolEngine {
	struct ApplicationConfiguration {
		int Width, Height;
		const char* Title;
	};

	class Application {
	public:
		virtual ~Application() = default;
		virtual bool init() { return true; }
		void run();
		virtual void shutdown() {}
	protected:
		Application() = default;
		Application(const ApplicationConfiguration&);
	private:
		ApplicationConfiguration mConfig;
	};

	extern Application* createApplication();
}