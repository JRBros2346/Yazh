#include"application.hpp"

#include"logger.hpp"

namespace Yazh {
	b Application::create(Game::game* _gameInst) {
		if(initialized) {
			YERROR("Application::create called more than once.")
			return false;
		}
		
		gameInst = _gameInst;
		
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
				gameInst->appConfig.name, 
				gameInst->appConfig.startPosX, 
				gameInst->appConfig.startPosY, 
				gameInst->appConfig.startWidth, 
				gameInst->appConfig.startHeight)) {
	   		return false;
		}
		
		// Initialize the game.
		if (!gameInst->_initialize(gameInst)) {
			YFATAL("Game failed to initialize.");
			return false;
		}
		
		gameInst->_onResize(gameInst, width, height);
		
		initialized = true;
		
		return true;
	}

	b Application::run() {
		while (isRunning) {
			if(!platform.pumpMessages()) {
				isRunning = false;
			}
			
			if(!isSuspended) {
				if (!gameInst->_update(gameInst, (f32)0)) {
					YFATAL("Game update failed, shutting down.")
					isRunning = false;
					break;
				}
			
				// Call the game's render routine.
				if (!gameInst->_render(gameInst, (f32)0)) {
					YFATAL("Game render failed, shutting down.")
					isRunning = false;
					break;
				}
			}
		}
		
		isRunning = false;
		
		platform.shutdown();
		return true;
	}
} // namespace Yazh
