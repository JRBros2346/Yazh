#include<core/logger.hpp>
#include<core/asserts.hpp>

/* TODO (#1#): Test */
#include<core/application.hpp>

int main(void) {
	// Application configuration.
	Yazh::Application::config appConfig;
	appConfig.startPosX = 100;
	appConfig.startPosY = 100;
	appConfig.startWidth = 1280;
	appConfig.startHeight = 720;
	appConfig.name = (char*)"Yazh Engine Testbed";
	Yazh::Application app;
	
	app.create(&appConfig);
	
	app.run();
}
