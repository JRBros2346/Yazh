#include<core/logger.hpp>
#include<core/asserts.hpp>

/* TODO (#1#): Test */
#include<core/application.hpp>

int main(void) {
	// Application configuration.
	Yazh::Application::startPosX = 100;
	Yazh::Application::startPosY = 100;
	Yazh::Application::startWidth = 1280;
	Yazh::Application::startHeight = 720;
	Yazh::Application::name = (char*)"Yazh Engine Testbed";
	Yazh::Application app;
	
	app.create();
	
	app.run();
}
