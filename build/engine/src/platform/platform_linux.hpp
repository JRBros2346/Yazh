#pragma once

#include"defines.hpp"
#include"core/logger.hpp"

#include<xcb/xcb.h>
#include<X11/keysym.h>
#include<X11/XKBlib.h>  	// sudo apt-get install libx11-dev
#include<X11/Xlib.h>
#include<X11/Xlib-xcb.h>	// sudo apt-get install libxkbcommon-x11-dev
#include<sys/time.h>

#include<chrono>
#include<thread> // std::this_thread::sleep_for(std::chrono::nanoseconds())

#include<cstdlib>
#include<cstring>
#include<iostream>

namespace Yazh {
	class YAPI Platform {
		Display* display;
		xcb_connection_t* connection;
		xcb_window_t window;
		xcb_screen_t* screen;
		xcb_atom_t wm_protocols;
		xcb_atom_t wm_delete_win;
		public:
			b startup(
				const char* application_name,
				i32 x,
				i32 y,
				i32 width,
				i32 height);
			
			void shutdown();
			
			b pumpMessages();
			
			void* allocate(u64 size, b aligned);
			void free(void* block, b aligned);
			void* zeroMemory(void* block, u64 size);
			void* copyMemory(void* dest, const void* source, u64 size);
			void* setMemory(void* dest, i32 value, u64 size);
			
			f64 getAbsoluteTime();
			
			// Sleep on the thread for the provided ms. This blocks the main thread.
			// Should only be used for giving time back to the OS for unused update power.
			// Therefore it is not exported.
			void sleep(u64 ms);
	};
} // namespace Yazh
