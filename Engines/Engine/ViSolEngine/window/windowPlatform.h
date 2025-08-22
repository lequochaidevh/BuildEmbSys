#pragma once

#include "window.h"

namespace ViSolEngine {
	//Factory class
	class  WindowPlatform
	{
        public:
            static NativeWindow* create(EWindowPlatformSpec spec);
        private:
            WindowPlatform() = default;
            WindowPlatform(WindowPlatform&) = default;
            ~WindowPlatform() = default;
	};	 
}