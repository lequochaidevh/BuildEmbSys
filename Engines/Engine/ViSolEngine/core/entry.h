#pragma once

#include"application.h"


int main() {
	ViSolEngine::Application* application = ViSolEngine::createApplication();
	std::cout << "After Create Application" << std::endl;
	if (application->init()) {
		LOG_INFO("Entry init");
		application->run();
	}

	application->shutdown();
	delete application;

	return 0;
}