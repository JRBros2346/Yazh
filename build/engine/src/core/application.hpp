#pragma once

#include"defines.hpp"

#include"platform/platform_win32.cpp"
#include"platform/platform_linux.cpp"

namespace Yazh {
	// Forward declaration.
	namespace Game {
		extern class Game : public GameState;
	}
	class YAPI Application {
		static Yazh::Game::Game* gameInst;
		static b isRunning;
		static b isSuspended;
		static Platform platform;
		static i16 width;
		static i16 height;
		static f64 lastTime;
	
		public:
			// Application configuration.
			struct config {
				// Window starting position x axis. If applicable.
				i16 startPosX;
				
				// Window starting position y axis. If applicable.
				i16 startPosY;
				
				// Window starting width. If applicable.
				i16 startWidth;
				
				// Window starting height. If applicable.
				i16 startHeight;
				
				// The application name used in windowing. If applicable.
				char* name;
			};

			static b initialized;
			
			b create(Yazh::Game::Game*);
			
			b run();
	};
	Yazh::Game::Game* Application::gameInst;
	b Application::isRunning;
	b Application::isSuspended;
	Platform Application::platform;
	i16 Application::width;
	i16 Application::height;
	f64 Application::lastTime;
	
	b Application::initialized = false;
} // namespace Yazh
