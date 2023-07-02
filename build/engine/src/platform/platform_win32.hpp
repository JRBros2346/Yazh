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
			
			bool startup(
					const char* applicationName,
					i32 x,
					i32 y,
					i32 width,
					i32 height) override {
				
				hInstance = GetModuleHandleA(0);
				
				// Setup and register window class.
				HICON icon = LoadIcon(hInstance, IDI_APPLICATION);
				WNDCLASSA wc;
				memset(&wc, 0, sizeof(wc));
				wc.style = CS_DBLCLKS; // Get double-clicks
				wc.lpfnWndProc = Win32ProcessMessage;
				wc.cbClsExtra = 0;
				wc.cbWndExtra = 0;
				wc.hInstance = hInstance;
				wc.hIcon = icon;
				wc.hCursor = LoadCursor(nullptr, IDC_ARROW);  // nullptr; // Manage the cursor manually
				wc.hbrBackground = nullptr;                   // Transparent
				wc.lpszClassName = "yazh_window_class";
				
				if (!RegisterClassA(&wc)) {
					MessageBoxA(0, "Window registration failed", "Error", MB_ICONEXCLAMATION | MB_OK);
					return false;
				}

				// Create window
				u32 clientX = x;
				u32 clientY = y;
				u32 clientWidth = width;
				u32 clientHeight = height;
				
				u32 windowX = clientX;
				u32 windowY = clientY;
				u32 windowWidth = clientWidth;
				u32 windowHeight = clientHeight;
				
				u32 windowStyle = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION;
				u32 windowExStyle = WS_EX_APPWINDOW;
				
				windowStyle |= WS_MAXIMIZEBOX;
				windowStyle |= WS_MINIMIZEBOX;
				windowStyle |= WS_THICKFRAME;
				
				// Obtain the size of the border.
				RECT borderRect{0, 0, 0, 0};
				AdjustWindowRectEx(&borderRect, windowStyle, 0, windowExStyle);
				
				// In this case, the border rectangle is negative.
				windowX += borderRect.left;
				windowY += borderRect.top;
				
				// Grow by the size of the OS border.
				windowWidth += borderRect.right - borderRect.left;
				windowHeight += borderRect.bottom - borderRect.top;
				
				HWND handle = CreateWindowExA(
					windowExStyle, "yazh_window_class", applicationName,
					windowStyle, windowX, windowY, windowWidth, windowHeight,
					0, 0, hInstance, 0);
				
				if (handle == nullptr) {
					MessageBoxA(NULL, "Window creation failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
					
					YFATAL("Window creation failed!");
					return false;
				} else {
					hwnd = handle;
				}
				
				// Show the window
				bool shouldActivate = true; /* TODO (#1#): if the window should not accept input, this should be false. */
				i32 showWindowCommandFlags = shouldActivate ? SW_SHOW : SW_SHOWNOACTIVATE;
				// If initially minimized, use SW_MINIMIZE : SW_SHOWMINNOACTIVE;
				// If initially maximized, use SW_SHOWMAXIMIZED : SW_MAXIMIZE
				ShowWindow(hwnd, showWindowCommandFlags);
				
				// Clock setup
				LARGE_INTEGER frequency;
				QueryPerformanceFrequency(&frequency);
				clockFrequency = 1.0 / (f64)frequency.QuadPart;
				QueryPerformanceCounter(&startTime);
				
				return true;
			}
					
			void shutdown() override {
				if (hwnd) {
					DestroyWindow(hwnd);
					hwnd = nullptr;
				}
			}
			
			bool pumpMessages() override {
				MSG message;
				while (PeekMessageA(&message, nullptr, 0, 0, PM_REMOVE)) {
					TranslateMessage(&message);
					DispatchMessageA(&message);
				}
				
				return true;
			}
			
			static void* allocate(u64, bool);
			static void free(void*, bool);
			static void* zeroMemory(void*, u64);
			static void* copyMemory(void*, const void*, u64);
			static void* setMemory(void*, i32, u64);
	};
} // namespace Yazh

#endif // YPLATFORM_WINDOWS