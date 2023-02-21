#include"platform/platform.hpp"

#if YPLATFORM_WINDOWS
	
#	include"core/logger.hpp"
	
#	include<windows.h>
#	include<windowsx.h> // param input extraction
#	include<iostream>

namespace Yazh {
	LRESULT CALLBACK win32_process_message(HWND hwnd, u32 msg, WPARAM w_param, LPARAM l_param);
	class YAPI Platform : public _Platform {
		HINSTANCE h_instance;
		HWND hwnd;
		
		public:
			// Clock
			static f64 clock_frequency;
			static LARGE_INTEGER start_time;
			
			b startup(
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
				b should_activate = true; /* TODO (#1#): if the window should not accept input, this should be false. */
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
			
			b pumpMessages() override {
				MSG message;
				while (PeekMessageA(&message, nullptr, 0, 0, PM_REMOVE)) {
					TranslateMessage(&message);
					DispatchMessageA(&message);
				}
				
				return true;
			}
			
			void shutdown() override {
				if (hwnd) {
					DestroyWindow(hwnd);
					hwnd = nullptr;
				}
			}
			
			void *allocate(u64 size, b aligned) override {
				return malloc(size);
			}
			
			void free(void *block, b alligned) override {
				::free(block);
			}
			
			void *zeroMemory(void *block, u64 size) override {
				return memset(block, 0, size);
			}
			
			void *copyMemory(void *dest, const void *source, u64 size) override {
				return memcpy(dest, source, size);
			}
			
			void *setMemory(void *dest, i32 value, u64 size) override {
				return memset(dest, value, size);
			}
			
			f64 getAbsoluteTime() override {
				LARGE_INTEGER now_time;
				QueryPerformanceCounter(&now_time);
				return (f64)now_time.QuadPart * Platform::clock_frequency;
			}
			
			void sleep(u64 ms) override {
				Sleep(ms);
			}
			
			Platform();
			~Platform();
	};
	
	f64 Platform::clock_frequency;
	LARGE_INTEGER Platform::start_time;
	
//	void consoleWrite(const std::string message, Logger::log_level color) {
//		// FATAL,ERROR,WARN,INFO,DEBUG,TRACE
//		// static u8 levels[6] = {64, 4, 6, 2, 1, 8};
//		std::clog << message << '\n';
//	}
			
//	void consoleWriteError(const std::string message, Logger::log_level color) {
//		// FATAL,ERROR,WARN,INFO,DEBUG,TRACE                                 
//		// static u8 levels[6] = {64, 4, 6, 2, 1, 8};
//		std::cerr << message << '\n';
//	}
	
	Platform::Platform() = default;
	Platform::~Platform() { shutdown(); }
	
	LRESULT CALLBACK win32_process_message(HWND hwnd, u32 msg, WPARAM w_param, LPARAM l_param) {
		switch (msg) {
			case WM_ERASEBKGND:
			// Notify the OS that erasing will be handled by the application to prevent flicker.
			return 1;
			case WM_CLOSE:
				/* TODO (#1#): Fire an event for the application to quit. */
				return 0;
			case WM_DESTROY:
				PostQuitMessage(0);
				return 0;
			case WM_SIZE: {
				// Get the updated size.
				// RECT r;
				// GetClientRect(hwnd, &r);
				// u32 width = r.right - r.left;
				// u32 height = r.bottom - r.top;
				
				/* TODO (#1#): Fire an event for window resize. */
			} break;
			case WM_KEYDOWN:
			case WM_SYSKEYDOWN:
			case WM_KEYUP:
			case WM_SYSKEYUP: {
				// Key pressed/released
				//b8 pressed = (msg == WM_KEYDOWN || msg == WM_SYSKEYDOWN);
				/* TODO (#1#): input processing. */
				
			} break;
			case WM_MOUSEMOVE: {
				// Mouse move
				//i32 x_position = GET_X_LPARAM(l_param);
				//i32 y_position = GET_Y_LPARAM(l_param);
				/* TODO (#1#): input processing. */
			} break;
			case WM_MOUSEWHEEL: {
				// i32 z_delta = GET_WHEEL_DELTA_WPARAM(w_param);
				// if (z_delta != 0) {
				//	// Flatten the input to an OS-independent (-1, 1)
				//	z_delta = (z_delta < 0) ? -1 : 1;
				//	/* TODO (#1#): input processing. */
				// }
			} break;
			case WM_LBUTTONDOWN:
			case WM_MBUTTONDOWN:
			case WM_RBUTTONDOWN:
			case WM_LBUTTONUP:
			case WM_MBUTTONUP:
			case WM_RBUTTONUP: {
				//b pressed = msg == WM_LBUTTONDOWN || msg == WM_RBUTTONDOWN || msg == WM_MBUTTONDOWN;
				/* TODO (#1#): input processing. */
			} break;
		}
		
		return DefWindowProcA(hwnd, msg, w_param, l_param);
	}
}
	
#endif // KPLATFORM_WINDOWS