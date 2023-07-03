// Windows platform layer.
#if YPLATFORM_WINDOWS
#	include"platform_win32.hpp"

namespace Yazh {
	f64 Platform::clockFrequency;
	LARGE_INTEGER Platform::startTime;

	bool Platform::startup(
			const char* applicationName,
			i32 x,
			i32 y,
			i32 width,
			i32 height) {
		
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
		auto shouldActivate = true; /* TODO (#1#): if the window should not accept input, this should be false. */
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
	
	void* Platform::allocate(u64 size, bool aligned) {
		return malloc(size);
	}

	void Platform::free(void *block, bool alligned) {
		::free(block);
	}

	void* Platform::zeroMemory(void *block, u64 size) {
		return memset(block, 0, size);
	}

	void* Platform::copyMemory(void *dest, const void *source, u64 size) {
		return memcpy(dest, source, size);
	}

	void* Platform::setMemory(void *dest, i32 value, u64 size) {
		return memset(dest, value, size);
	}
		
	LRESULT CALLBACK Platform::Win32ProcessMessage(HWND hwnd, u32 msg, WPARAM wParam, LPARAM lParam) {
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
			case WM_SIZE: 
				// Get the updated size.
				// RECT r;
				// GetClientRect(hwnd, &r);
				// u32 width = r.right - r.left;
				// u32 height = r.bottom - r.top;

				/* TODO (#1#): Fire an event for window resize. */
				break;
			case WM_KEYDOWN:
			case WM_SYSKEYDOWN:
			case WM_KEYUP:
			case WM_SYSKEYUP:
				// Key pressed/released
				//b8 pressed = (msg == WM_KEYDOWN || msg == WM_SYSKEYDOWN);
				/* TODO (#1#): input processing. */

				break;
			case WM_MOUSEMOVE:
				// Mouse move
				//i32 xPosition = GET_X_LPARAM(lParam);
				//i32 yPosition = GET_Y_LPARAM(lParam);
				/* TODO (#1#): input processing. */
				break;
			case WM_MOUSEWHEEL:
				// i32 deltaZ = GET_WHEEL_DELTA_WPARAM(wParam);
				// if (deltaZ != 0) {
				//	// Flatten the input to an OS-independent (-1, 1)
				//	deltaZ = (deltaZ < 0) ? -1 : 1;
				//	/* TODO (#1#): input processing. */
				// }
				break;
			case WM_LBUTTONDOWN:
			case WM_MBUTTONDOWN:
			case WM_RBUTTONDOWN:
			case WM_LBUTTONUP:
			case WM_MBUTTONUP:
			case WM_RBUTTONUP:
				//bool pressed = msg == WM_LBUTTONDOWN || msg == WM_RBUTTONDOWN || msg == WM_MBUTTONDOWN;
				/* TODO (#1#): input processing. */
				break;
		}

		return DefWindowProcA(hwnd, msg, wParam, lParam);
	}
}

#endif // YPLATFORM_WINDOWS
