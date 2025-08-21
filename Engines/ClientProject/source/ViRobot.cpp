#include"ViSolEngine/core/entry.h"
#include"ViSolEngine/core/logger/logger.h"

class ViRobot : public ViSolEngine::Application {
public:
	ViRobot(const ViSolEngine::ApplicationConfiguration& config) : ViSolEngine::Application(config) {
		LOG_INFO("ViRobot client constructor init");
	}
	virtual bool init() override {
		LOG_INFO("ViRobot is init");
		return true;
	}
	virtual void shutdown() override {
		LOG_INFO("ViRobot is shutdown");
	}

};

ViSolEngine::Application* ViSolEngine::createApplication() {
	std::cout << "----- Start CreateApplication -----" << std::endl;
	ViSolEngine::ApplicationConfiguration appConfig;
	appConfig.width = 800;
	appConfig.height = 600;
	appConfig.title = "ViSolEngine version 1.0.0";

	return new ViRobot(appConfig);
}
