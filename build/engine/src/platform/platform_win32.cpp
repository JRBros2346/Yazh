// Windows platform layer.
#include"platform_win32.hpp"

#if YPLATFORM_WINDOWS
#	include"core/logger.hpp"
#	include"core/input.hpp"

namespace Yazh {
	f64 Platform::clock_frequency;
	LARGE_INTEGER Platform::start_time;
	DWORD Platform::dwPrevOutMode = 0;

	inline bool Platform::startup(
			const char* application_name,
			i32 x,
			i32 y,
			i32 width,
			i32 height) {

		hInstance = GetModuleHandleA(nullptr);
		
		auto hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleMode(hOutput, &dwPrevOutMode);
		auto dwReqOutMode = ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN;
		auto dwOutMode = dwPrevOutMode | dwReqOutMode;
		if (!SetConsoleMode(hOutput, dwOutMode)) {
			Core::Logger::Info("Fallback to Enable Newline Auto Return...");
			dwReqOutMode = ENABLE_VIRTUAL_TERMINAL_PROCESSING;
			dwOutMode = dwPrevOutMode | dwReqOutMode;
			SetConsoleMode(hOutput, dwOutMode);
		}

		// Setup and register window class.
		auto hIcon = LoadIcon(hInstance, IDI_APPLICATION);
		WNDCLASSEXA wc = {};
		wc.style = CS_DBLCLKS; // Get double-clicks
		wc.lpfnWndProc = Win32ProcessMessage;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInstance;
		wc.hIcon = hIcon;
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);  // nullptr; // Manage the cursor manually
		wc.hbrBackground = nullptr;                   // Transparent
		wc.lpszClassName = "yazh_window_class";
		wc.cbSize = sizeof(WNDCLASSEXW);

		if (!RegisterClassExA(&wc)) {
			MessageBoxA(nullptr, "Window registration failed", "Error", MB_ICONEXCLAMATION | MB_OK);
			return false;
		}
			// Create window
		auto clientX = x;
		auto clientY = y;
		auto nClientWidth = width;
		auto nClientHeight = height;

		auto windowX = clientX;
		auto windowY = clientY;
		auto nWindowWidth = nClientWidth;
		auto nWindowHeight = nClientHeight;

		auto dwWindowStyle = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION;
		auto dwWindowExStyle = WS_EX_APPWINDOW;

		dwWindowStyle |= WS_MAXIMIZEBOX;
		dwWindowStyle |= WS_MINIMIZEBOX;
		dwWindowStyle |= WS_THICKFRAME;

		// Obtain the size of the border.
		RECT rectBorder = {};
		AdjustWindowRectEx(&rectBorder, dwWindowStyle, 0, dwWindowExStyle);

		// In this case, the border rectangle is negative.
		windowX += rectBorder.left;
		windowY += rectBorder.top;

		// Grow by the size of the OS border.
		nWindowWidth += rectBorder.right - rectBorder.left;
		nWindowHeight += rectBorder.bottom - rectBorder.top;

		HWND handle = CreateWindowExA(
			dwWindowExStyle, "yazh_window_class", application_name,
			dwWindowStyle, windowX, windowY, nWindowWidth, nWindowHeight,
			nullptr, nullptr, hInstance, nullptr);

		if (handle == nullptr) {
			MessageBoxA(nullptr, "Window creation failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);

			Core::Logger::Fatal("Window creation failed!");
			return false;
		} else {
			hWnd = handle;
		}

		// Show the window
		auto should_activate = true; // TODO: if the window should not accept input, this should be false.
		auto dwShowWindowCommandFlags = should_activate ? SW_SHOW : SW_SHOWNOACTIVATE;
		// If initially minimized, use SW_MINIMIZE : SW_SHOWMINNOACTIVE;
		// If initially maximized, use SW_SHOWMAXIMIZED : SW_MAXIMIZE
		ShowWindow(hWnd, dwShowWindowCommandFlags);

		// Clock setup
		LARGE_INTEGER lFrequency;
		QueryPerformanceFrequency(&lFrequency);
		clock_frequency = 1.0 / (f64)lFrequency.QuadPart;
		QueryPerformanceCounter(&start_time);

		return true;
	}

	inline void Platform::shutdown() {
		SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), dwPrevOutMode);
		if (hWnd) {
			DestroyWindow(hWnd);
			hWnd = nullptr;
		}
	}

	inline bool Platform::pumpMessages() {
		MSG message;
		while (PeekMessageA(&message, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&message);
			DispatchMessageA(&message);
		}

		return true;
	}

	inline void* Platform::allocate(std::size_t size, bool aligned) {
		return ::operator new(size);
	}

	inline void Platform::free(void *block, std::size_t size, bool alligned) {
		::operator delete(block, size);
	}

	inline void* Platform::zeroMemory(void *block, std::size_t size) {
		return memset(block, 0, size);
	}

	inline void* Platform::copyMemory(void *dest, const void *source, std::size_t size) {
		return memcpy(dest, source, size);
	}

	inline void* Platform::setMemory(void *dest, i32 value, std::size_t size) {
		return memset(dest, value, size);
	}

	LRESULT CALLBACK Platform::Win32ProcessMessage(HWND hWnd, u32 msg, WPARAM wp, LPARAM lp) {
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
				// GetClientRect(hWnd, &r);
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
				auto key = (Core::Input::Key)wp;
				
				// Pass to the input subsystem for processing.
				Core::Input::process(key, pressed);
			} break;
			case WM_MOUSEMOVE: {
				// Mouse move
				i32 x = GET_X_LPARAM(lp);
				i32 y = GET_Y_LPARAM(lp);

				// Pass over to the input subsystem.
				Core::Input::process(x, y);
			} break;
			case WM_MOUSEWHEEL: {
				i32 z_delta = GET_WHEEL_DELTA_WPARAM(wp);
				if (z_delta != 0) {
					// Flatten the input to an OS-independent (-1, 1)
					z_delta = (z_delta < 0) ? -1 : 1;
					
					Core::Input::process(z_delta);
				}
			} break;
			case WM_LBUTTONDOWN:
			case WM_MBUTTONDOWN:
			case WM_RBUTTONDOWN:
			case WM_LBUTTONUP:
			case WM_MBUTTONUP:
			case WM_RBUTTONUP: {
				auto pressed = msg == WM_LBUTTONDOWN || msg == WM_RBUTTONDOWN || msg == WM_MBUTTONDOWN;
				auto button = Core::Input::Button::MAX;
				switch(msg) {
					case WM_LBUTTONDOWN:
					case WM_LBUTTONUP:
						button = Core::Input::Button::Left;
						break;
					case WM_MBUTTONDOWN:
					case WM_MBUTTONUP:
						button = Core::Input::Button::Middle;
						break;
					case WM_RBUTTONDOWN:
					case WM_RBUTTONUP:
						button = Core::Input::Button::Right;
						break;
				}

				// Pass over to the input subsystem.
				if (button != Core::Input::Button::MAX)
					Core::Input::process(button, pressed);
			} break;
		}

		return DefWindowProcA(hWnd, msg, wp, lp);
	}
} // namespace Yazh

#endif // YPLATFORM_WINDOWS
