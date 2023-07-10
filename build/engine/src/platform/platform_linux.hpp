#pragma once

#include"platform.hpp"
#include"defines.hpp"

#if YPLATFORM_LINUX
#	include<xcb/xcb.h>
#	include<X11/keysym.h>
#	include<X11/XKBlib.h>  	// sudo apt-get install libx11-dev
#	include<X11/Xlib.h>
#	include<X11/Xlib-xcb.h>	// sudo apt-get install libxkbcommon-x11-dev
#	include<sys/time.h>

namespace Yazh {
	class YAPI Platform : public VirtualPlatform {
		Display* display;
		xcb_connection_t* connection;
		xcb_window_t window;
		xcb_screen_t* screen;
		xcb_atom_t wm_protocols;
		xcb_atom_t wm_delete_win;

		public:
			bool startup(const char*, i32, i32, i32, i32);
			void shutdown();
			bool pumpMessages();

			static void* allocate(ysize, bool);
			static void free(void*, ysize, bool);
			static void* zeroMemory(void*, ysize);
			static void* copyMemory(void*, const void*, ysize);
			static void* setMemory(void*, i32, ysize);
	};
} // namespace Yazh

#endif // YPLATFORM_LINUX
