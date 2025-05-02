#pragma once

/*Define enum InputCode TO Adapter*/
namespace VIEngine {
	enum class EKeyState {
		None,
		Pressed,
		Held,
		Released
	};
	/*reference in glfw3.h -> Not use it because software will depended on Vendors tightly, so hard for optimized*/
	enum class EKeyCode {
		SPACE = 32,
		APOSTROPHE = 39,  /* ' */
		COMMA = 44,  /* , */
		MINUS = 45,  /* - */
		PERIOD = 46,  /* . */
		SLASH = 47,  /* / */
		NUM_0 = 48,
		NUM_1 = 49,
		NUM_2 = 50,
		...
	};

	enum class EMouseButton {
		BUTTON_1 = 0,
		BUTTON_2 = 1,
		BUTTON_3 = 2,
		BUTTON_4 = 3,
		BUTTON_5 = 4,
		BUTTON_6 = 5,
		BUTTON_7 = 6,
		BUTTON_8 = 7,
		...
	};
}


#pragma once
#include"pch.h"
#include"KeyCode.h"

class GLFWwindow;

namespace VIEngine {
	/*9.1.1.1_Interface KeyboardInput*/
	class VI_API KeyboardInput {
	public:
		virtual ~KeyboardInput() = default;
		//getValue-> replace func isHeld not use at glfw
		VI_FORCE_INLINE int8_t getValue(EKeyCode keyCode) const { return (isPressed(keyCode) || isHeld(keyCode)) ? 1 : 0; }

		VI_FORCE_INLINE EKeyState getState(EKeyCode keyCode) { return getState((int32_t)keyCode); }
		VI_FORCE_INLINE bool isPressed(EKeyCode keyCode) const { return isPressed((int32_t)keyCode); }
		VI_FORCE_INLINE bool isHeld(EKeyCode keyCode) const { return isHeld((int32_t)keyCode); } //Can not use by glfw
		VI_FORCE_INLINE bool isReleased(EKeyCode keyCode) const { return isReleased((int32_t)keyCode); }

		virtual EKeyState getState(int32_t keyCode) const = 0;
		virtual bool isPressed(int32_t keyCode) const = 0;
		virtual bool isHeld(int32_t keyCode) const = 0;
		virtual bool isReleased(int32_t keyCode) const = 0;
	protected:
		KeyboardInput() = default;
	};
	/*9.1.1.2_Create GLFWKeyboard: KeyboardInput*/
	class VI_API GLFWKeyboardInput : public KeyboardInput {
	public:
		GLFWKeyboardInput(void* window);
		virtual EKeyState getState(int32_t keyCode) const override;
		virtual bool isPressed(int32_t keyCode) const override;
		virtual bool isHeld(int32_t keyCode) const override;
		virtual bool isReleased(int32_t keyCode) const override;
	private:
		GLFWwindow* mWindow;
	};
	/*9.1.1.5_Interface MouseInput & GLFWMouseInput:*/
	class VI_API MouseInput {
	public:
		virtual ~MouseInput() = default;
		VI_FORCE_INLINE int8_t getValue(EMouseButton button) const { return (isPressed(button) || isHeld(button)) ? 1 : 0; }

		VI_FORCE_INLINE EKeyState  getState(EKeyState  button) { return getState((int32_t)button); }
		VI_FORCE_INLINE bool isPressed(EMouseButton button) const { return isPressed((int32_t)button); }
		VI_FORCE_INLINE bool isHeld(EMouseButton button) const { return isHeld((int32_t)button); } //Can not use by glfw
		VI_FORCE_INLINE bool isReleased(EMouseButton button) const { return isReleased((int32_t)button); }
		virtual EKeyState  getState(int32_t button) const = 0;
		virtual bool isPressed(int32_t button) const = 0;
		virtual bool isHeld(int32_t button) const = 0;
		virtual bool isReleased(int32_t button) const = 0;

		VI_FORCE_INLINE float getPositionX() const { return mX; }
		VI_FORCE_INLINE float getPositionY() const { return mY; }
		VI_FORCE_INLINE float getOffsetX() const { return mOffsetX; }
		VI_FORCE_INLINE float getOffsetY() const { return mOffsetY; }
		VI_FORCE_INLINE float getSrollX() const { return mScrollX; }
		VI_FORCE_INLINE float getSrollY() const { return mScrollY; }

		VI_FORCE_INLINE void setPosition(float x, float y) { mX = x; mY = y; }
		VI_FORCE_INLINE void setPositionX(float x) { mX = x; }
		VI_FORCE_INLINE void setPositionY(float y) { mY = y; }

		VI_FORCE_INLINE void setOffset(float offsetX, float offsetY) { mOffsetX = offsetX; mOffsetY = offsetY; }
		VI_FORCE_INLINE void setOffsetX(float offsetX) { mOffsetX = offsetX; }
		VI_FORCE_INLINE void setOffsetY(float offsetY) { mOffsetY = offsetY; }

		VI_FORCE_INLINE void setScroll(float scrollX, float scrollY) { mScrollX = scrollX; mScrollY = scrollY; }
		VI_FORCE_INLINE void setSrollX(float scrollX) { mScrollX = scrollX; }
		VI_FORCE_INLINE void setSrollY(float scrollY) { mScrollY = scrollY; }


	protected:
		MouseInput() = default;
	protected:
		float mX, mY;
		float mOffsetX, mOffsetY;
		float mScrollX, mScrollY;
	};

	class VI_API GLFWMouseInput : public MouseInput {
	public:
		GLFWMouseInput(void* window);
		virtual EKeyState getState(int32_t button) const override;
		virtual bool isPressed(int32_t button) const override;
		virtual bool isHeld(int32_t button) const override;
		virtual bool isReleased(int32_t button) const override;
	private:
		GLFWwindow* mWindow;
	};
	struct VI_API InputState {
		KeyboardInput* Keyboard;
		MouseInput* Mouse;
	};

}




//GLFWInput.cpp
#include "InputState.h"

#include <GLFW/glfw3.h>

class GLFWwindow;

namespace VIEngine {
	/*9.1.1.4_Create func check and convert type to enum class*/
	static EKeyState GLFWToEngineKeyState(int32_t action) {
		if (action == GLFW_PRESS) return EKeyState::Pressed;
		if (action == GLFW_REPEAT) return EKeyState::Held;
		if (action == GLFW_RELEASE) return EKeyState::Released;
		return EKeyState::None;
	}

	/*9.1.1.3_Define func in GLFWKeyboard*/
	GLFWKeyboardInput::GLFWKeyboardInput(void* window) {
		mWindow = (GLFWwindow*)window;
	}
	EKeyState GLFWKeyboardInput::getState(int32_t keyCode) const {
		return GLFWToEngineKeyState(glfwGetKey(mWindow, keyCode));
	}
	bool GLFWKeyboardInput::isPressed(int32_t keyCode) const {
		return glfwGetKey(mWindow, keyCode) == GLFW_PRESS;
	}

	bool GLFWKeyboardInput::isHeld(int32_t keyCode) const {
		// TODO: Not use this method, it not work on GLFW
		return glfwGetKey(mWindow, keyCode) == GLFW_REPEAT;
	}
	bool GLFWKeyboardInput::isReleased(int32_t keyCode) const {
		return glfwGetKey(mWindow, keyCode) == GLFW_RELEASE;
	}

	GLFWMouseInput::GLFWMouseInput(void* window) {
		mWindow = (GLFWwindow*)window;
	}
	EKeyState GLFWMouseInput::getState(int32_t button) const {
		return GLFWToEngineKeyState(glfwGetMouseButton(mWindow, button));
	}

	bool GLFWMouseInput::isPressed(int32_t button) const {
		return glfwGetMouseButton(mWindow, button) == GLFW_PRESS;
	}

	bool GLFWMouseInput::isHeld(int32_t button) const {
		// TODO: Not use this method, it not work on GLFW
		return glfwGetMouseButton(mWindow, button) == GLFW_REPEAT;
	}

	bool GLFWMouseInput::isReleased(int32_t button) const {
		return glfwGetMouseButton(mWindow, button) == GLFW_RELEASE;
	}

}


















