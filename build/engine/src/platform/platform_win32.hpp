#pragma once

#include"platform.hpp"
#include"defines.hpp"
#include"core/logger.hpp"

#if YPLATFORM_WINDOWS
#	include<windows.h>
#	include<windowsx.h> // param input extraction

namespace Yazh {
	class YAPI Platform : public VirtualPlatform {
		static LRESULT CALLBACK win32_process_message(HWND hwnd, u32 msg, WPARAM w_param, LPARAM l_param);
		
		HINSTANCE h_instance;
		HWND hwnd;
		
		public:
			// Clock
			static f64 clock_frequency;
			static LARGE_INTEGER start_time;
			
			bool startup(
					const char *application_name,
					i32 x,
					i32 y,
					i32 width,
					i32 height) override {
				
				h_instance = GetModuleHandleA(0);
				
				// Setup and register window class.
				HICON icon = LoadIcon(h_instance, IDI_APPLICATION);
				WNDCLASSA wc;
				memset(&wc, 0, sizeof(wc));
				wc.style = CS_DBLCLKS; // Get double-clicks
				wc.lpfnWndProc = win32_process_message;
				wc.cbClsExtra = 0;
				wc.cbWndExtra = 0;
				wc.hInstance = h_instance;
				wc.hIcon = icon;
				wc.hCursor = LoadCursor(nullptr, IDC_ARROW);  // nullptr; // Manage the cursor manually
				wc.hbrBackground = nullptr;                   // Transparent
				wc.lpszClassName = "yazh_window_class";
				
				if (!RegisterClassA(&wc)) {
					MessageBoxA(0, "Window registration failed", "Error", MB_ICONEXCLAMATION | MB_OK);
					return false;
				}

				// Create window
				u32 client_x = x;
				u32 client_y = y;
				u32 client_width = width;
				u32 client_height = height;
				
				u32 window_x = client_x;
				u32 window_y = client_y;
				u32 window_width = client_width;
				u32 window_height = client_height;
				
				u32 window_style = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION;
				u32 window_ex_style = WS_EX_APPWINDOW;
				
				window_style |= WS_MAXIMIZEBOX;
				window_style |= WS_MINIMIZEBOX;
				window_style |= WS_THICKFRAME;
				
				// Obtain the size of the border.
				RECT border_rect{0, 0, 0, 0};
				AdjustWindowRectEx(&border_rect, window_style, 0, window_ex_style);
				
				// In this case, the border rectangle is negative.
				window_x += border_rect.left;
				window_y += border_rect.top;
				
				// Grow by the size of the OS border.
				window_width += border_rect.right - border_rect.left;
				window_height += border_rect.bottom - border_rect.top;
				
				HWND handle = CreateWindowExA(
					window_ex_style, "yazh_window_class", application_name,
					window_style, window_x, window_y, window_width, window_height,
					0, 0, h_instance, 0);
				
				if (handle == nullptr) {
					MessageBoxA(NULL, "Window creation failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
					
					YFATAL("Window creation failed!");
					return false;
				} else {
					hwnd = handle;
				}
				
				// Show the window
				bool should_activate = true; /* TODO (#1#): if the window should not accept input, this should be false. */
				i32 show_window_command_flags = should_activate ? SW_SHOW : SW_SHOWNOACTIVATE;
				// If initially minimized, use SW_MINIMIZE : SW_SHOWMINNOACTIVE;
				// If initially maximized, use SW_SHOWMAXIMIZED : SW_MAXIMIZE
				ShowWindow(hwnd, show_window_command_flags);
				
				// Clock setup
				LARGE_INTEGER frequency;
				QueryPerformanceFrequency(&frequency);
				clock_frequency = 1.0 / (f64)frequency.QuadPart;
				QueryPerformanceCounter(&start_time);
				
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
			
			static void* allocate(u64 size, bool aligned);
			static void free(void* block, bool aligned);
			static void* zeroMemory(void* block, u64 size);
			static void* copyMemory(void* dest, const void* source, u64 size);
			static void* setMemory(void* dest, i32 value, u64 size);
	};
} // namespace Yazh

#endif // YPLATFORM_WINDOWS