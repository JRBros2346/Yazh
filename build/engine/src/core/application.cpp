#include"application.hpp"

#include"logger.hpp"

/**
 * Application Layer is not Object Oriented.
 * Because, it is hardcoded to exist only one at a time
 * So, it is optimized for speed by sacrificing OOPS
 */

namespace Yazh::Application {
	static struct {
		bool isRunning;
		bool isSuspended;
		Yazh::Platform platform;
		i16 width;
		i16 height;
		f64 lastTime;
	} state;
	
	static bool initialized = false;
	
	bool create(config* appConfig) {
		if(initialized) {
			YERROR("Yazh::Application::create called more than once.");
			return false;
		}
		
		// Initialize subsystems.
		Yazh::Logger::initializeLogging();
		
		/* TODO (#1#): Remove this */
		YFATAL("A test message: ",3.14f);
		YERROR("A test message: ",3.14f);
		YWARN("A test message: ",3.14f);
		YINFO("A test message: ",3.14f);
		YDEBUG("A test message: ",3.14f);
		YTRACE("A test message: ",3.14f);
		
		state.isRunning = true;
		state.isSuspended = false;
		
		if(!state.platform.startup(
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
	
	bool run() {
		while(state.isRunning) {
			if(!state.platform.pumpMessages()) {
				state.isRunning = false;
			}
		}
		
		state.isRunning = false;
		
		state.platform.shutdown();
		
		return true;
	}
} // namespace Yazh::Application
