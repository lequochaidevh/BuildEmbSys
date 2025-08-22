#include "windowPlatform.h"
#include "pch.h"
#include "../core/logger/logger.h"

namespace ViSolEngine {
	NativeWindow* WindowPlatform::create(EWindowPlatformSpec spec) {
		NativeWindow* window = nullptr;

		switch (spec)
		{
            case ViSolEngine::EWindowPlatformSpec::SDL: VISOL_ASSERT("SDL Window not supported");
            case ViSolEngine::EWindowPlatformSpec::None: VISOL_ASSERT("Unknown Window detected");
            case ViSolEngine::EWindowPlatformSpec::GLFW: window = new GLFWPlatformWindow();
		    default: VISOL_ASSERT("Unknown Window detected");
		}
		return dynamic_cast<NativeWindow*>(window);
	}
}