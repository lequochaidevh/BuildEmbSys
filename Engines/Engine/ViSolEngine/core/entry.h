#pragma once

#include"application.h"


int main() {
	ViSolEngine::Logger::init();
	
	ViSolEngine::Application* application = ViSolEngine::createApplication();
	LOG_INFO("After Create Application");
	if (application->init()) {
		LOG_INFO("Entry init");
		application->run();
	}

	application->shutdown();
	VISOL_FREE_MEMORY(application);

	std::cin.get();
	return 0;
}