#pragma once
/*2*/
#include"pch.h"
#include"keyCode.h"

/*NOTE: This class belong library GLFW, not contain into Engine*/
class GLFWwindow;

namespace ViSolEngine {
	/*Interface KeyboardInput*/
	class VISOL_API KeyboardInput {
	public:
		virtual ~KeyboardInput() = default;
		// getValue-> replace func isHeld not use at glfw
		VISOL_FORCE_INLINE int8_t getValue(EKeyCode keyCode) const { return (isPressed(keyCode) || isHeld(keyCode)) ? 1 : 0; }
		VISOL_FORCE_INLINE EKeyState getState(EKeyCode keyCode) { return getState((int32_t)keyCode); }
		VISOL_FORCE_INLINE bool isPressed(EKeyCode keyCode) const { return isPressed((int32_t)keyCode); }
		
		/* --- Not be supported by glfw --- */
		VISOL_FORCE_INLINE bool isHeld(EKeyCode keyCode) const { return isHeld((int32_t)keyCode); } 
		/* --- Not be supported by glfw --- */
		
		VISOL_FORCE_INLINE bool isReleased(EKeyCode keyCode) const { return isReleased((int32_t)keyCode); }

		virtual EKeyState getState(int32_t keyCode) const = 0;
		virtual bool isPressed(int32_t keyCode) const = 0;
		virtual bool isHeld(int32_t keyCode) const = 0;
		virtual bool isReleased(int32_t keyCode) const = 0;
	protected:
		KeyboardInput() = default;
	};

	/**/
	class VISOL_API GLFWKeyboardInput : public KeyboardInput {
	public:
		GLFWKeyboardInput(void* window);
		virtual EKeyState getState(int32_t keyCode) const override;
		virtual bool isPressed(int32_t keyCode) const override;

		/* --- Not be supported by glfw --- */
		virtual bool isHeld(int32_t keyCode) const override;
		/* --- Not be supported by glfw --- */

		virtual bool isReleased(int32_t keyCode) const override;
	private:
		GLFWwindow* mWindow;
	};

	/*Interface MouseInput*/
	class VISOL_API MouseInput {
	public:
		virtual ~MouseInput() = default;
		VISOL_FORCE_INLINE int8_t getValue(EMouseButton button) const { return (isPressed(button) || isHeld(button)) ? 1 : 0; }

		VISOL_FORCE_INLINE EKeyState  getState(EKeyState  button) { return getState((int32_t)button); }
		VISOL_FORCE_INLINE bool isPressed(EMouseButton button) const { return isPressed((int32_t)button); }
		VISOL_FORCE_INLINE bool isHeld(EMouseButton button) const { return isHeld((int32_t)button); } //Can not use by glfw
		VISOL_FORCE_INLINE bool isReleased(EMouseButton button) const { return isReleased((int32_t)button); }
		virtual EKeyState  getState(int32_t button) const = 0;
		virtual bool isPressed(int32_t button) const = 0;
		virtual bool isHeld(int32_t button) const = 0;
		virtual bool isReleased(int32_t button) const = 0;

		VISOL_FORCE_INLINE float getPositionX() const { return mX; }
		VISOL_FORCE_INLINE float getPositionY() const { return mY; }
		VISOL_FORCE_INLINE float getOffsetX() const { return mOffsetX; }
		VISOL_FORCE_INLINE float getOffsetY() const { return mOffsetY; }
		VISOL_FORCE_INLINE float getSrollX() const { return mScrollX; }
		VISOL_FORCE_INLINE float getSrollY() const { return mScrollY; }

		VISOL_FORCE_INLINE void setPosition(float x, float y) { mX = x; mY = y; }
		VISOL_FORCE_INLINE void setPositionX(float x) { mX = x; }
		VISOL_FORCE_INLINE void setPositionY(float y) { mY = y; }

		VISOL_FORCE_INLINE void setOffset(float offsetX, float offsetY) { mOffsetX = offsetX; mOffsetY = offsetY; }
		VISOL_FORCE_INLINE void setOffsetX(float offsetX) { mOffsetX = offsetX; }
		VISOL_FORCE_INLINE void setOffsetY(float offsetY) { mOffsetY = offsetY; }

		VISOL_FORCE_INLINE void setScroll(float scrollX, float scrollY) { mScrollX = scrollX; mScrollY = scrollY; }
		VISOL_FORCE_INLINE void setSrollX(float scrollX) { mScrollX = scrollX; }
		VISOL_FORCE_INLINE void setSrollY(float scrollY) { mScrollY = scrollY; }


	protected:
		MouseInput() = default;
	protected:
		float mX, mY;
		float mOffsetX, mOffsetY;
		float mScrollX, mScrollY;
	};

	class VISOL_API GLFWMouseInput : public MouseInput {
	public:
		GLFWMouseInput(void* window);
		virtual EKeyState getState(int32_t button) const override;
		virtual bool isPressed(int32_t button) const override;

		/* --- Not be supported by glfw --- */
		virtual bool isHeld(int32_t button) const override;
		/* --- Not be supported by glfw --- */

		virtual bool isReleased(int32_t button) const override;
	private:
		GLFWwindow* mWindow;
	};

	struct VISOL_API InputState {
		KeyboardInput* Keyboard;
		MouseInput* Mouse;
	};

}