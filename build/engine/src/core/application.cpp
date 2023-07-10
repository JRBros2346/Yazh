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
		VirtualGame* game;
		bool is_running;
		bool is_suspended;
		Platform platform;
		i16 width;
		i16 height;
		f64 last_time;
	} state;

	// Event handlers
	bool onEvent(u16, Event::Sender*, Event::Listener*, Event::Context);
	bool onKey(u16, Event::Sender*, Event::Listener*, Event::Context);
	
	bool create(VirtualGame* game) {
		if(initialized) {
			YERROR("Yazh::Application::create called more than once.");
			return false;
		}
		
		state.game = game;
		
		// Initialize subsystems.
		Logger::initialize();
		Input::initialize();
		
		// TODO: Remove this
		YFATAL("A test message: ",3.14f);
		YERROR("A test message: ",3.14f);
		YWARN("A test message: ",3.14f);
		YINFO("A test message: ",3.14f);
		YDEBUG("A test message: ",3.14f);
		YTRACE("A test message: ",3.14f);
		
		state.is_running = true;
		state.is_suspended = false;

		if (!Event::initialize()) {
			YFATAL("Event system failed initialization. Application cannot continue.");
			return false;
		}

		Event::Register((u16)Event::SystemCode::ApplicationQuit, nullptr, onEvent);
		Event::Register((u16)Event::SystemCode::KeyPressed, nullptr, onEvent);
		Event::Register((u16)Event::SystemCode::KeyReleased, nullptr, onEvent);
		
		if(!state.platform.startup(
				game->app_config.name,
				game->app_config.start_pos_x,
				game->app_config.start_pos_y,
				game->app_config.start_width,
				game->app_config.start_height))
			return false;
		
		if(!state.game->initialize()) {
			YFATAL("Game failed to initialize.");
			return false;
		}
		
		state.game->onResize(state.width, state.height);
		
		initialized = true;
		
		return true;
	}
	
	bool run() {
		YINFO(Memory::getMemoryUsageString());
		while (state.is_running) {
			if (!state.platform.pumpMessages())
				state.is_running = false;
			
			if (!state.is_suspended) {
				if (!state.game->update((f32)0)) {
					state.is_running = false;
					break;
				}
				
				// Calls the game's render routine.
				if (!state.game->render((f32)0)) {
					state.is_running = false;
					break;
				}

				// NOTE: Input update/state copying should always be handled
				// after any input should be recorded; I.E. before this line.
				// As a safety, input is the last thing to be updated before
				// this frame ends;
				Input::update(0);
			}
		}
		
		state.is_running = false;

		// Shutdown event system.
		Event::Unregister((u16)Event::SystemCode::ApplicationQuit, nullptr, onEvent);
		Event::Unregister((u16)Event::SystemCode::KeyPressed, nullptr, onEvent);
		Event::Unregister((u16)Event::SystemCode::KeyReleased, nullptr, onEvent);
		Event::shutdown();
		Input::shutdown();
		
		state.platform.shutdown();
		
		return true;
	}

	bool onEvent(u16 code, Event::Sender* sender, Event::Listener* listenerInst, Event::Context context) {
		switch (code) {
			case (u16)Event::SystemCode::ApplicationQuit: {
				YINFO("Yazh::Event::SystemCode::ApplicationQuit received, shutting down.\n");
				state.is_running = false;
				return true;
			}
			default:
				return false;
		}
	}

	bool onKey(u16 code, Event::Sender* sender, Event::Listener* listenerInst, Event::Context context) {
		if (code == (u16)Event::SystemCode::KeyPressed) {
			auto key = (Input::Key)context.U16[0];
			if (key == Input::Key::Esc) {
				// NOTE: Technically firing an event to itself, but there may be other listeners.
				Event::Fire((u16)Event::SystemCode::ApplicationQuit, nullptr, {});

				// Block anything else from processing this.
				return true;
			} else if (key == Input::Key::A) {
				// Example on checking for a key
				YDEBUG("Explicit - A key pressed!");
			} else {
				YDEBUG('\'', (char)key, "' key pressed in window.");
			}
		} else if (code == (u16)Event::SystemCode::KeyReleased) {
			auto key = (Input::Key)context.U16[0];
			if (key == Input::Key::B) {
				// Example on checking for a key
				YDEBUG("Explicit - B key released!");
			} else {
				YDEBUG('\'', (char)key, "' key released in window.");
			}
		}
		return false;
	}
} // namespace Yazh::Application
