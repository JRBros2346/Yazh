#pragma once

#include"defines.hpp"

// Forward declaration
namespace Yazh { class VirtualGame; }

namespace Yazh::Application {
	// Application configuration.
	using config = struct config {
		// Window starting position x axis. If applicable.
		i16 start_pos_x;
		
		// Window starting position y axis. If applicable.
		i16 start_pos_y;
		
		// Window starting width. If applicable.
		i16 start_width;
		
		// Window starting height. If applicable.
		i16 start_height;
		
		// The application name used in windowing. If applicable.
		char* name;
	};
	
	
	YAPI bool create(Yazh::VirtualGame*);
	
	YAPI bool run();
} // namespace Yazh::Application
