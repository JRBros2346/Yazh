#include"application.hpp"
#include"game_types.hpp"

#include"logger.hpp"

#include"platform/platform_win32.hpp"
#include"platform/platform_linux.hpp"
#include"ymemory.hpp"
#include"event.hpp"
#include"input.hpp"

/* Application Layer is NOT Object Oriented.
 * Because, it is hardcoded to exist only one at a time
 * So, it is optimized for speed by sacrificing OOPS
 */

namespace Yazh::Core::Application {
	static auto initialized = false;
	static struct state {
		Game::VirtualGame* game;
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
	
	inline bool create(Game::VirtualGame* game) {
		if(initialized) {
			Core::Logger::Error("Yazh::Application::create called more than once.");
			return false;
		}
		
		state.game = game;
		
		// Initialize subsystems.
		Logger::initialize();
		Input::initialize();
		
		// TODO: Remove this
		Core::Logger::Fatal("A test message: {}",3.14f);
		Core::Logger::Error("A test message: {}",3.14f);
		Core::Logger::Warn("A test message: {}",3.14f);
		Core::Logger::Info("A test message: {}",3.14f);
		Core::Logger::Debug("A test message: {}",3.14f);
		Core::Logger::Trace("A test message: {}",3.14f);
		
		state.is_running = true;
		state.is_suspended = false;

		if (!Event::initialize()) {
			Core::Logger::Fatal("Event system failed initialization. Application cannot continue.");
			return false;
		}

		Event::Register(static_cast<u16>(Event::SystemCode::ApplicationQuit), nullptr, onEvent);
		Event::Register(static_cast<u16>(Event::SystemCode::KeyPressed), nullptr, onKey);
		Event::Register(static_cast<u16>(Event::SystemCode::KeyReleased), nullptr, onKey);
		
		if(!state.platform.startup(
				game->app_config.name,
				game->app_config.start_pos_x,
				game->app_config.start_pos_y,
				game->app_config.start_width,
				game->app_config.start_height))
			return false;
		
		if(!state.game->initialize()) {
			Core::Logger::Fatal("Game failed to initialize.");
			return false;
		}
		
		state.game->onResize(state.width, state.height);
		
		initialized = true;
		
		return true;
	}
	
	inline bool run() {
		Info(Memory::getMemoryUsageString());
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
		Event::Unregister(static_cast<u16>(Event::SystemCode::ApplicationQuit), nullptr, onEvent);
		Event::Unregister(static_cast<u16>(Event::SystemCode::KeyPressed), nullptr, onKey);
		Event::Unregister(static_cast<u16>(Event::SystemCode::KeyReleased), nullptr, onKey);
		Event::shutdown();
		Input::shutdown();
		
		state.platform.shutdown();
		
		return true;
	}

	bool onEvent(u16 code, Event::Sender* sender, Event::Listener* listenerInst, Event::Context context) {
		switch (code) {
			case static_cast<u16>(Event::SystemCode::ApplicationQuit): {
				Logger::Info("Yazh::Event::SystemCode::ApplicationQuit received, shutting down.");
				state.is_running = false;
				return true;
			}
			default:
				return false;
		}
	}

	bool onKey(u16 code, Event::Sender* sender, Event::Listener* listenerInst, Event::Context context) {
		if (code == static_cast<u16>(Event::SystemCode::KeyPressed)) {
			auto key = static_cast<Input::Key>(context.U16[0]);
			if (key == Input::Key::Esc) {
				// NOTE: Technically firing an event to itself, but there may be other listeners.
				Event::Fire(static_cast<u16>(Event::SystemCode::ApplicationQuit), nullptr, {});

				// Block anything else from processing this.
				return true;
			} else if (key == Input::Key::A) {
				// Example on checking for a key
				Logger::Debug("Explicit - A key pressed!");
			} else {
				Logger::Debug("'{}' key pressed in window.", (char)static_cast<u8>(key));
			}
		} else if (code == static_cast<u16>(Event::SystemCode::KeyReleased)) {
			auto key = static_cast<Input::Key>(context.U16[0]);
			if (key == Input::Key::B) {
				// Example on checking for a key
				Logger::Debug("Explicit - B key released!");
			} else {
				Logger::Debug("'{}' key released in window.", (char)static_cast<u8>(key));
			}
		}
		return false;
	}
} // namespace Yazh::Core::Application
