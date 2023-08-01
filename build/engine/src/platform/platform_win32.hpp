#pragma once

#include"defines.hpp"
#include"platform.hpp"

#if YPLATFORM_WINDOWS
#	include<windows.h>
#	include<windowsx.h> // param input extraction

namespace Yazh {
	class YAPI Platform : virtual VirtualPlatform {
		static LRESULT CALLBACK Win32ProcessMessage(HWND, u32, WPARAM, LPARAM);
		
		HINSTANCE hInstance;
		HWND hWnd;
		static DWORD dwPrevOutMode;

		public:
			// Clock
			static f64 clock_frequency;
			static LARGE_INTEGER start_time;

			bool startup(const char*, i32, i32, i32, i32) final;
			void shutdown() final;
			bool pumpMessages() final;

			static void* allocate(ysize, bool);
			static void free(void*, ysize, bool);
			static void* zeroMemory(void*, ysize);
			static void* copyMemory(void*, const void*, ysize);
			static void* setMemory(void*, i32, ysize);

			static u64 getAbsoluteTime();

			// Sleep on the thread for the provided ms. This blocks the main thread.
			// Should only be used for giving time back to the OS for unused update power.
			// Therefore it is not exported.
			static void sleep(u64);
	};
} // namespace Yazh

#endif // YPLATFORM_WINDOWS
