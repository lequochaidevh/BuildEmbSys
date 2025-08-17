#include"ViSolEngine/core/entry.h"
#include"ViSolEngine/core/logger/logger.h"

class ViRobot : public ViSolEngine::Application {
public:
	ViRobot(const ViSolEngine::ApplicationConfiguration& config) : ViSolEngine::Application(config) {
		std::cout << "ViRobot is config >> ViRobot.cpp\n";
		LOG_INFO("Info works:");
		LOG_TRACE("Trace works");
		LOG_WARN("Warn works");
		LOG_ERROR("Error works");
		LOG_CRITICAL("Critical works");
	}
	virtual bool init() override {
		std::cout << "ViRobot is init >> ViRobot.cpp\n";
		return true;
	}
	virtual void shutdown() override {
		std::cout << "ViRobot is shutdown >> ViRobot.cpp\n";
	}

};
ViSolEngine::Application* ViSolEngine::createApplication() {
	std::cout << "Start CreateApplication >> ViRobot.cpp\n";
	ViSolEngine::ApplicationConfiguration appConfig;
	appConfig.Width = 800;
	appConfig.Height = 600;
	appConfig.Title = "ViSolEngine Alpha ver 1";

	return new ViRobot(appConfig);
}