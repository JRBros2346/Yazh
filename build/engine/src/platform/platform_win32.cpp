// Windows platform layer.
#if YPLATFORM_WINDOWS
#	include"platform_win32.hpp"

#	include"core/logger.hpp"
#	include"core/input.hpp"

namespace Yazh {
	f64 Platform::clock_frequency;
	LARGE_INTEGER Platform::start_time;

	bool Platform::startup(
			const char* application_name,
			i32 x,
			i32 y,
			i32 width,
			i32 height) {

		h_instance = GetModuleHandleA(0);

		// Setup and register window class.
		HICON icon = LoadIcon(h_instance, IDI_APPLICATION);
		WNDCLASSA wc;
		memset(&wc, 0, sizeof(wc));
		wc.style = CS_DBLCLKS; // Get double-clicks
		wc.lpfnWndProc = Win32ProcessMessage;
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
		auto should_activate = true; // TODO: if the window should not accept input, this should be false.
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

	void Platform::shutdown() {
		if (hwnd) {
			DestroyWindow(hwnd);
			hwnd = nullptr;
		}
	}

	bool Platform::pumpMessages() {
		MSG message;
		while (PeekMessageA(&message, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&message);
			DispatchMessageA(&message);
		}

		return true;
	}

	void* Platform::allocate(ysize size, bool aligned) {
		return ::operator new(size);
	}

	void Platform::free(void *block, ysize size, bool alligned) {
		::operator delete(block, size);
	}

	void* Platform::zeroMemory(void *block, ysize size) {
		return memset(block, 0, size);
	}

	void* Platform::copyMemory(void *dest, const void *source, ysize size) {
		return memcpy(dest, source, size);
	}

	void* Platform::setMemory(void *dest, i32 value, ysize size) {
		return memset(dest, value, size);
	}

	LRESULT CALLBACK Platform::Win32ProcessMessage(HWND hwnd, u32 msg, WPARAM wp, LPARAM lp) {
		switch (msg) {
			case WM_ERASEBKGND:
				// Notify the OS that erasing will be handled by the application to prevent flicker.
				return 1;
			case WM_CLOSE:
				// TODO: Fire an event for the application to quit.
				return 0;
			case WM_DESTROY:
				PostQuitMessage(0);
				return 0;
			case WM_SIZE:
				// Get the updated size.
				// RECT r;
				// GetClientRect(hwnd, &r);
				// u32 width = r.right - r.left;
				// u32 height = r.bottom - r.top;

				// TODO: Fire an event for window resize.
				break;
			case WM_KEYDOWN:
			case WM_SYSKEYDOWN:
			case WM_KEYUP:
			case WM_SYSKEYUP: {
				// Key pressed/released
				auto pressed = (msg == WM_KEYDOWN || msg == WM_SYSKEYDOWN);
				auto key = (Input::Key)wp;
				
				// Pass to the input subsystem for processing.
				Input::process(key, pressed);
			} break;
			case WM_MOUSEMOVE: {
				// Mouse move
				i32 x = GET_X_LPARAM(lp);
				i32 y = GET_Y_LPARAM(lp);

				// Pass over to the input subsystem.
				Input::process(x, y);
			} break;
			case WM_MOUSEWHEEL: {
				i32 z_delta = GET_WHEEL_DELTA_WPARAM(wp);
				if (z_delta != 0) {
					// Flatten the input to an OS-independent (-1, 1)
					z_delta = (z_delta < 0) ? -1 : 1;
					
					Input::process(z_delta);
				}
			} break;
			case WM_LBUTTONDOWN:
			case WM_MBUTTONDOWN:
			case WM_RBUTTONDOWN:
			case WM_LBUTTONUP:
			case WM_MBUTTONUP:
			case WM_RBUTTONUP: {
				auto pressed = msg == WM_LBUTTONDOWN || msg == WM_RBUTTONDOWN || msg == WM_MBUTTONDOWN;
				auto button = Input::Button::MAX;
				switch(msg) {
					case WM_LBUTTONDOWN:
					case WM_LBUTTONUP:
						button = Input::Button::Left;
						break;
					case WM_MBUTTONDOWN:
					case WM_MBUTTONUP:
						button = Input::Button::Middle;
						break;
					case WM_RBUTTONDOWN:
					case WM_RBUTTONUP:
						button = Input::Button::Right;
						break;
				}

				// Pass over to the input subsystem.
				if (button != Input::Button::MAX)
					Input::process(button, pressed);
			} break;
		}

		return DefWindowProcA(hwnd, msg, wp, lp);
	}
}

#endif // YPLATFORM_WINDOWS
