#pragma once

#include"defines.hpp"

#include"platform/platform_win32.hpp"
#include"platform/platform_linux.hpp"

namespace Yazh {
	class YAPI Application {
		static bool isRunning;
		static bool isSuspended;
		static Platform platform;
		i16 width;
		i16 height;
		f64 last_time;
	
		public:
			// Application configuration.
			using config = struct {
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
			
			static bool initialized;
			
			bool create(config*);
			
			bool run();
	};
	bool Application::isRunning;
	bool Application::isSuspended;
	Platform Application::platform;
	
	bool Application::initialized = false;
} // namespace Yazh
