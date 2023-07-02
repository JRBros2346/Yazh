// Windows platform layer.
#if YPLATFORM_WINDOWS
#	include"platform_win32.hpp"

namespace Yazh {
	f64 Platform::clockFrequency;
	LARGE_INTEGER Platform::startTime;
	
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
