#pragma once

#include"defines.hpp"

#include"platform/platform_win32.cpp"
#include"platform/platform_linux.cpp"

namespace Yazh {
	class YAPI Application {
		static b is_running;
		static b is_suspended;
		static Platform platform;
		static i16 width;
		static i16 height;
		static f64 last_time;
	
		public:
			// Application configuration.
			typedef struct {
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
			} config;

			static b initialized;
			
			b create(config*);
			
			b run();
	};
	b Application::is_running;
	b Application::is_suspended;
	Platform Application::platform;
	i16 Application::width;
	i16 Application::height;
	f64 Application::last_time;
	
	b Application::initialized = false;
} // namespace Yazh
