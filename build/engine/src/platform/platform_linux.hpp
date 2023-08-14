#pragma once

#include"defines.hpp"
#include"platform.hpp"

#if YPLATFORM_LINUX
#	include<xcb/xcb.h>
#	include<X11/keysym.h>
#	include<X11/XKBlib.h>  	// sudo apt-get install libx11-dev
#	include<X11/Xlib.h>
#	include<X11/Xlib-xcb.h>	// sudo apt-get install libxkbcommon-x11-dev
#	include<sys/time.h>

namespace Yazh {
	class YAPI Platform : virtual VirtualPlatform {
		Display* display;
		xcb_connection_t* connection;
		xcb_window_t window;
		xcb_screen_t* screen;
		xcb_atom_t wm_protocols;
		xcb_atom_t wm_delete_win;

		public:
			bool startup(const char*, i32, i32, i32, i32) final;
			void shutdown() final;
			bool pumpMessages() final;

			static void* allocate(std::size_t, bool);
			static void free(void*, std::size_t, bool);
			static void* zeroMemory(void*, std::size_t);
			static void* copyMemory(void*, const void*, std::size_t);
			static void* setMemory(void*, i32, std::size_t);

			static u64 getAbsoluteTime();

			// Sleep on the thread for the provided ms. This blocks the main thread.
			// Should only be used for giving time back to the OS for unused update power.
			// Therefore it is not exported.
			static void sleep(u64);
	};
} // namespace Yazh

#endif // YPLATFORM_LINUX
