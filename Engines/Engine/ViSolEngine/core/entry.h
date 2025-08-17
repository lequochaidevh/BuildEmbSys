#pragma once

#include"application.h"


int main() {
	std::cout << "Main Entry.h \n";
	ViSolEngine::Application* application = ViSolEngine::createApplication();
	std::cout << "After CreateApplication Entry.h\n";
	if (application->init()) {
		std::cout << "Init Entry.h \n";
		application->run();
	}

	application->shutdown();
	delete application;

	return 0;
}