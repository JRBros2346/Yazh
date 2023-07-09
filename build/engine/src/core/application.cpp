#include"application.hpp"
#include"game_types.hpp"

#include"logger.hpp"

#include"platform/platform_win32.cpp"
#include"platform/platform_linux.cpp"
#include"ymemory.hpp"
#include"event.hpp"
#include"input.hpp"

/* Application Layer is NOT Object Oriented.
 * Because, it is hardcoded to exist only one at a time
 * So, it is optimized for speed by sacrificing OOPS
 */

namespace Yazh::Application {
	static auto initialized = false;
	static struct state {
		Yazh::VirtualGame* game;
		bool isRunning;
		bool isSuspended;
		Yazh::Platform platform;
		i16 width;
		i16 height;
		f64 lastTime;
	} state;

	// Event handlers
	bool onEvent(u16, Yazh::Event::Sender*, Yazh::Event::Listener*, Yazh::Event::Context);
	bool onKey(u16, Yazh::Event::Sender*, Yazh::Event::Listener*, Yazh::Event::Context);
	
	bool create(Yazh::VirtualGame* game) {
		if(initialized) {
			YERROR("Yazh::Application::create called more than once.");
			return false;
		}
		
		state.game = game;
		
		// Initialize subsystems.
		Yazh::Logger::initialize();
		Yazh::Input::initialize();
		
		// TODO: Remove this
		YFATAL("A test message: ",3.14f);
		YERROR("A test message: ",3.14f);
		YWARN("A test message: ",3.14f);
		YINFO("A test message: ",3.14f);
		YDEBUG("A test message: ",3.14f);
		YTRACE("A test message: ",3.14f);
		
		state.isRunning = true;
		state.isSuspended = false;

		if (!Yazh::Event::initialize()) {
			YFATAL("Event system failed initialization. Application cannot continue.");
			return false;
		}

		Yazh::Event::Register((u16)Yazh::Event::SystemCode::ApplicationQuit, 0, onEvent);
		Yazh::Event::Register((u16)Yazh::Event::SystemCode::KeyPressed, 0, onEvent);
		Yazh::Event::Register((u16)Yazh::Event::SystemCode::KeyReleased, 0, onEvent);
		
		if(!state.platform.startup(
				game->appConfig.name,
				game->appConfig.start_pos_x,
				game->appConfig.start_pos_y,
				game->appConfig.start_width,
				game->appConfig.start_height)) {
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
		YINFO(Yazh::Memory::getMemoryUsageString());
		while (state.isRunning) {
			if (!state.platform.pumpMessages()) {
				state.isRunning = false;
			}
			
			if (!state.isSuspended) {
				if (!state.game->update((f32)0)) {
					state.isRunning = false;
					break;
				}
				
				// Calls the game's render routine.
				if (!state.game->render((f32)0)) {
					state.isRunning = false;
					break;
				}

				// NOTE: Input update/state copying should always be handled
				// after any input should be recorded; I.E. before this line.
				// As a safety, input is the last thing to be updated before
				// this frame ends;
				Yazh::Input::update(0);
			}
		}
		
		state.isRunning = false;

		// Shutdown event system.
		Yazh::Event::Unregister((u16)Yazh::Event::SystemCode::ApplicationQuit, 0, onEvent);
		Yazh::Event::Unregister((u16)Yazh::Event::SystemCode::KeyPressed, 0, onEvent);
		Yazh::Event::Unregister((u16)Yazh::Event::SystemCode::KeyReleased, 0, onEvent);
		Yazh::Event::shutdown();
		Yazh::Input::shutdown();
		
		state.platform.shutdown();
		
		return true;
	}

	bool onEvent(u16 code, Yazh::Event::Sender* sender, Yazh::Event::Listener* listenerInst, Yazh::Event::Context context) {
		switch ((Yazh::Event::SystemCode)code) {
			case Yazh::Event::SystemCode::ApplicationQuit: {
				YINFO("Yazh::Event::SystemCode::ApplicationQuit received, shutting down.\n");
				state.isRunning = false;
				return true;
			}
			default:
				return false;
		}
	}

	bool onKey(u16 code, Yazh::Event::Sender* sender, Yazh::Event::Listener* listenerInst, Yazh::Event::Context context) {
		if (code == (u16)Yazh::Event::SystemCode::KeyPressed) {
			auto key = (Yazh::Input::Key)context.data.U16[0];
			if (key == Yazh::Input::Key::Esc) {
				// NOTE: Technically firing an event to itself, but there may be other listeners.
				Yazh::Event::Fire((u16)Yazh::Event::SystemCode::ApplicationQuit, nullptr, {});

				// Block anything else from processing this.
				return true;
			} else if (key == Yazh::Input::Key::A) {
				// Example on checking for a key
				YDEBUG("Explicit - A key pressed!");
			} else {
				YDEBUG('\'', (char)key, "' key pressed in window.")
			}
		} else if (code == (u16)Yazh::Event::SystemCode::KeyReleased) {
			auto key = (Yazh::Input::Key)context.data.U16[0];
			if (key == Yazh::Input::Key::B) {
				// Example on checking for a key
				YDEBUG("Explicit - B key released!");
			} else {
				YDEBUG('\'', (char)key, "' key released in window.")
			}
		}
		return false;
	}
} // namespace Yazh::Application
