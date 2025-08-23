#pragma once

class GLFWwindow;
namespace ViSolEngine {
	enum class  EWindowPlatformSpec
	{
		GLFW,
		SDL,
		None
	};

	/*for close source*/
	class EventDispatcher;

	typedef struct windownData_t {
		int32_t width, height;
		EventDispatcher* pEventDispatcher;
	} windownData_t;
	class NativeWindow
	{
	public:
		virtual ~NativeWindow() = default;
		virtual bool init(const struct ApplicationConfiguration&, EventDispatcher*) = 0;
		virtual void shutdown() = 0;
		virtual void swapbuffers() = 0;
		virtual void pollsEvent() = 0;
		virtual bool shouldClose() = 0;
		
	private:

	protected:
		NativeWindow() = default;
		NativeWindow(NativeWindow&) = default;
	};
	class GLFWPlatformWindow : public NativeWindow
	{
	public:
		virtual bool init(const struct ApplicationConfiguration&, EventDispatcher*) override;
		virtual void shutdown() override;
		virtual void swapbuffers() override;
		virtual void pollsEvent() override;
		virtual bool shouldClose() override;

		GLFWPlatformWindow();
		~GLFWPlatformWindow();
	private:
		GLFWwindow* mWindow;
		windownData_t mData;
	protected:
	};
	
}