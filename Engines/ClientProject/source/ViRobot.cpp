#include"ViSolEngine/core/entry.h"
#include"ViSolEngine/core/logger/logger.h"

class ViRobot : public ViSolEngine::Application {
public:
	ViRobot(const ViSolEngine::ApplicationConfiguration& config) : ViSolEngine::Application(config) {
		LOG_INFO("Info works");
		LOG_TRACE("Trace works");
		LOG_WARN("Warn works");
		LOG_ERROR("Error works");
		LOG_CRITICAL("Critical works");
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
	appConfig.Width = 800;
	appConfig.Height = 600;
	appConfig.Title = "ViSolEngine version 1.0.0";

	return new ViRobot(appConfig);
}
