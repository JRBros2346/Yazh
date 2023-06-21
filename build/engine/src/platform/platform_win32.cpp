// Windows platform layer.
#if YPLATFORM_WINDOWS
#	include"platform_win32.hpp"

namespace Yazh {
	f64 Platform::clock_frequency;
	LARGE_INTEGER Platform::start_time;
	
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
		
	LRESULT CALLBACK Platform::win32_process_message(HWND hwnd, u32 msg, WPARAM w_param, LPARAM l_param) {
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
				//bool pressed = msg == WM_LBUTTONDOWN || msg == WM_RBUTTONDOWN || msg == WM_MBUTTONDOWN;
				/* TODO (#1#): input processing. */
			} break;
		}

		return DefWindowProcA(hwnd, msg, w_param, l_param);
	}
}

#endif // YPLATFORM_WINDOWS
