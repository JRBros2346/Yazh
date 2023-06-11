#pragma once

#include"defines.hpp"

#include<platform/platform_win32.cpp>
#include<platform/platform_linux.cpp>

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
			// Window starting position x axis. If applicable.
			static i16 startPosX;
			// Window starting position y axis. If applicable.
			static i16 startPosY;
			// Window starting width. If applicable.
			static i16 startWidth;
			// Window starting height. If applicable.
			static i16 startHeight;
			// The application name used in windowing. If applicable.
			static char* name;
			
			static b initialized;
			
			b create();
			
			b run();
	};
	b Application::is_running;
	b Application::is_suspended;
	Platform Application::platform;
	i16 Application::width;
	i16 Application::height;
	f64 Application::last_time;
	
	i16 Application::startPosX;
	i16 Application::startPosY;
	i16 Application::startWidth;
	i16 Application::startHeight;
	char* Application::name;
	
	b Application::initialized = false;
} // namespace Yazh
