#pragma once

/*1*/
#include "pch.h"

namespace ViSolEngine {
	class VISOL_API EventContext {
	public:
		virtual ~EventContext() = default;
	};

	class VISOL_API WindowResizedEvent : public EventContext {
	public:
		WindowResizedEvent(int32_t width, int32_t height) : mWidth(width)
            , mHeight(height) {}
            
		VISOL_FORCE_INLINE int32_t getWidth() const { return mWidth; }
		VISOL_FORCE_INLINE int32_t getHeight() const { return mHeight; }
	private:
		int32_t mWidth, mHeight;
	};
}