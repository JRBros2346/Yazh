#pragma once

#include"defines.hpp"

#include"platform/platform_win32.hpp"
#include"platform/platform_linux.hpp"

namespace Yazh::Application {
	// Application configuration.
	using config = struct config {
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
	
	
	YAPI bool create(config* appConfig);
	
	YAPI bool run();
} // namespace Yazh::Application
