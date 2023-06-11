#pragma once

#include"defines.hpp"
#include"core/logger.hpp"

#include<windows.h>
#include<windowsx.h> // param input extraction
#include<iostream>

namespace Yazh {
	LRESULT CALLBACK win32_process_message(HWND hwnd, u32 msg, WPARAM w_param, LPARAM l_param);
	class YAPI Platform {
		HINSTANCE h_instance;
		HWND hwnd;
		
		public:
			// Clock
			static f64 clock_frequency;
			static LARGE_INTEGER start_time;
			
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
			
			virtual f64 getAbsoluteTime();
			
			// Sleep on the thread for the provided ms. This blocks the main thread.
			// Should only be used for giving time back to the OS for unused update power.
			// Therefore it is not exported.
			virtual void sleep(u64 ms);
	};
} // namespace Yazh

