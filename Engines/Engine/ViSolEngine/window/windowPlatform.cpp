#include "windowPlatform.h"
#include "pch.h"

namespace ViSolEngine
{
	NativeWindow *WindowPlatform::create(EWindowPlatformSpec spec)
	{
		NativeWindow *window = nullptr;

		switch (spec)
		{
		case ViSolEngine::EWindowPlatformSpec::SDL:
			VISOL_ASSERT("SDL Window not supported");
		case ViSolEngine::EWindowPlatformSpec::None:
			VISOL_ASSERT("Unknown Window detected");
		case ViSolEngine::EWindowPlatformSpec::GLFW:
			window = new GLFWPlatformWindow();
		default:
			VISOL_ASSERT("Unknown Window detected");
		}
		return window;
	}
	KeyboardInput *WindowPlatform::createKeyboard(EWindowPlatformSpec spec, void *window)
	{

		KeyboardInput *input = nullptr;
		switch (spec)
		{
		case ViSolEngine::EWindowPlatformSpec::GLFW:
			input = new GLFWKeyboardInput(window);
			break;
		case ViSolEngine::EWindowPlatformSpec::SDL:
			VISOL_ASSERT("SDL Keyboard Input supported");
			break;
		case ViSolEngine::EWindowPlatformSpec::None:
			VISOL_ASSERT("Unknown Keyboard Input detected");
			break;
		default:
			VISOL_ASSERT("Unknown Keyboard detected");
		}
		return input;
	}

	MouseInput *WindowPlatform::createMouse(EWindowPlatformSpec spec, void *window)
	{
		MouseInput *input = nullptr;
		switch (spec)
		{
		case ViSolEngine::EWindowPlatformSpec::GLFW:
			input = new GLFWMouseInput(window);
			break;
		case ViSolEngine::EWindowPlatformSpec::SDL:
			VISOL_ASSERT("SDL Mouse Input supported");
			break;
		case ViSolEngine::EWindowPlatformSpec::None:
			VISOL_ASSERT("Unknown Mouse Input detected");
			break;
		default:
			VISOL_ASSERT("Unknown Mouse detected");
		}
		return input;
	}
}