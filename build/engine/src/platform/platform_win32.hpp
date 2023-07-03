#pragma once

#include"platform.hpp"
#include"defines.hpp"
#include"core/logger.hpp"

#if YPLATFORM_WINDOWS
#	include<windows.h>
#	include<windowsx.h> // param input extraction

namespace Yazh {
	class YAPI Platform : public VirtualPlatform {
		static LRESULT CALLBACK Win32ProcessMessage(HWND, u32, WPARAM, LPARAM);
		
		HINSTANCE hInstance;
		HWND hwnd;
		
		public:
			// Clock
			static f64 clockFrequency;
			static LARGE_INTEGER startTime;
			
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

#endif // YPLATFORM_WINDOWS