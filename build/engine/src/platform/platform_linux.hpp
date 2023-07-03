#pragma once

#include"platform.hpp"
#include"defines.hpp"
#include"core/logger.hpp"

#if YPLATFORM_LINUX
#	include<xcb/xcb.h>
#	include<X11/keysym.h>
#	include<X11/XKBlib.h>  	// sudo apt-get install libx11-dev
#	include<X11/Xlib.h>
#	include<X11/Xlib-xcb.h>	// sudo apt-get install libxkbcommon-x11-dev
#	include<sys/time.h>

#	include<cstdlib>
#	include<cstring>

namespace Yazh {
	class YAPI Platform : public VirtualPlatform {
		Display* display;
		xcb_connection_t* connection;
		xcb_window_t window;
		xcb_screen_t* screen;
		xcb_atom_t wmProtocols;
		xcb_atom_t wmDeleteWin;
		
		public:
			bool startup(const char*, i32, i32, i32, i32);
			void shutdown();
			bool pumpMessages();
			
			static void* allocate(u64, bool);
			static void free(void*, bool);
			static void* zeroMemory(void*, u64);
			static void* copyMemory(void*, const void*, u64);
			static void* setMemory(void*, i32, u64);
	};
} // namespace Yazh

#endif // YPLATFORM_LINUX