#include"application.hpp"

#include"logger.hpp"

namespace Yazh {
	b Application::create(config* appConfig) {
		if(initialized) {
			YERROR("Application::create called more than once.")
			return false;
		}
		
		// Initialize subsystems.
		Logger::initializeLogging();
		
		/* TODO (#1#): Remove this */
		YFATAL("A test message: ",3.14f);
		YERROR("A test message: ",3.14f);
		YWARN("A test message: ",3.14f);
		YINFO("A test message: ",3.14f);
		YDEBUG("A test message: ",3.14f);
		YTRACE("A test message: ",3.14f);
		
		is_running = true;
		is_suspended = false;
		
		if (!platform.startup(
				appConfig->name, 
				appConfig->startPosX, 
				appConfig->startPosY, 
				appConfig->startWidth, 
				appConfig->startHeight)) {
	   		return false;
		}
		
		initialized = true;
		
		return true;
	}

	b Application::run() {
		while (is_running) {
			if(!platform.pumpMessages()) {
				is_running = false;
			}
		}
		
		is_running = false;
		
		platform.shutdown();
		return true;
	}
} // namespace Yazh
