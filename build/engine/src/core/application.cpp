#include"application.hpp"
#include"game_types.hpp"

#include"platform/platform_win32.cpp"
#include"platform/platform_linux.cpp"

#include"logger.hpp"

/* Application Layer is NOT Object Oriented.
 * Because, it is hardcoded to exist only one at a time
 * So, it is optimized for speed by sacrificing OOPS
 */

namespace Yazh::Application {
	static struct state {
		Yazh::VirtualGame* game;
		bool isRunning;
		bool isSuspended;
		Yazh::Platform platform;
		i16 width;
		i16 height;
		f64 lastTime;
	} state;
	
	static bool initialized = false;
	
	bool create(Yazh::VirtualGame* game) {
		if(initialized) {
			YERROR("Yazh::Application::create called more than once.");
			return false;
		}
		
		state.game = game;
		
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
				game->appConfig.name,
				game->appConfig.startPosX,
				game->appConfig.startPosY,
				game->appConfig.startWidth,
				game->appConfig.startHeight)) {
			return false;
		}
		
		if(!state.game->initialize()) {
			YFATAL("Game failed to initialize.");
			return false;
		}
		
		state.game->onResize(state.width, state.height);
		
		initialized = true;
		
		return true;
	}
	
	bool run() {
		while (state.isRunning) {
			if (!state.platform.pumpMessages()) {
				state.isRunning = false;
			}
			
			if (!state.isSuspended) {
				// Call the game's update routine.
				if (!state.game->update((f32)0)) {
					state.isRunning = false;
					break;
				}
				
				// Calls the game's render routine.
				if (!state.game->render((f32)0)) {
					state.isRunning = false;
					break;
				}
			}
		}
		
		state.isRunning = false;
		
		state.platform.shutdown();
		
		return true;
	}
} // namespace Yazh::Application
