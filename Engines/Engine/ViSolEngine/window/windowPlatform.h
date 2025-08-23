#pragma once

#include "window.h"
namespace ViSolEngine {
	// Factory class
	class  WindowPlatform
	{
        public:
            static NativeWindow* create(EWindowPlatformSpec spec);
            /*Add create ptr Keyboard Mouse */
            static class KeyboardInput* createKeyboard(EWindowPlatformSpec spec, void* window);
            static class MouseInput* createMouse(EWindowPlatformSpec spec, void* window);
        private:
            WindowPlatform() = default;
            WindowPlatform(WindowPlatform&) = default;
            ~WindowPlatform() = default;
	};	 
}