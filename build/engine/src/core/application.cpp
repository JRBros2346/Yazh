#include"application.hpp"

#include"logger.hpp"

namespace Yazh {
	bool Application::create(config* appConfig) {
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
		
		isRunning = true;
		isSuspended = false;
		
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

	bool Application::run() {
		while (isRunning) {
			if(!platform.pumpMessages()) {
				isRunning = false;
			}
		}
		
		isRunning = false;
		
		platform.shutdown();
		return true;
	}
} // namespace Yazh
