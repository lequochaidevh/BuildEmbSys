#include "window.h"

#include "pch.h"
#include "core/logger/logger.h"
#include "core/application.h"
#define GLFW_GL_IMPLEMENTATION
#include <glad/gl.h>
#include<GLFW/glfw3.h>

namespace ViSolEngine {
	GLFWPlatformWindow::GLFWPlatformWindow() : mWindow(nullptr) {
        CORE_LOG_INFO("Call constructure GLFW");
	}
	GLFWPlatformWindow::~GLFWPlatformWindow() {
		
	}
	bool GLFWPlatformWindow::init(const ApplicationConfiguration& config) {
		if (!glfwInit()) {
			CORE_LOG_CRITICAL("GLFW Init failed");
			glfwTerminate();
			return false;
		}
		CORE_LOG_INFO("GLFW Init success");

		// Setup context for Opengl 4.3 Core
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		mWindow = glfwCreateWindow(config.width, config.height, config.title, nullptr, nullptr);
		if (!mWindow) {
			CORE_LOG_CRITICAL("Window created failed");
			glfwTerminate();
			return false;
		}
		CORE_LOG_INFO("Window created success");
		
		glfwMakeContextCurrent(mWindow);

		//Check to see if window can successfully interact
		if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress)) {
			CORE_LOG_CRITICAL("Glad load failed");
			glfwTerminate();
			return false;
		}
		CORE_LOG_INFO("Glad load success");

		return true;
	}
	void GLFWPlatformWindow::shutdown() {
		glfwTerminate();
	}
	void GLFWPlatformWindow::swapbuffers() {
		glClearColor(0.3f, 0.3f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(mWindow);
	}
	void GLFWPlatformWindow::pollsEvent() {
		glfwPollEvents();
	}
	bool GLFWPlatformWindow::shouldClose() {
		return glfwWindowShouldClose(mWindow);
	}
}