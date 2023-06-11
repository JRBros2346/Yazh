#include<core/logger.hpp>
#include<core/asserts.hpp>

/* TODO (#1#): Test */
#include<core/application.hpp>

int main(void) {
	// Application configuration.
	Yazh::Application.config.startPosX = 100;
	Yazh::Application.config.startPosY = 100;
	Yazh::Application.config.startWidth = 1280;
	Yazh::Application.config.startHeight = 720;
	Yazh::Application.config.name = "Yazh Engine Testbed";
	Yazh::Application app;
	
	app.create();
	
	app.run()
}
