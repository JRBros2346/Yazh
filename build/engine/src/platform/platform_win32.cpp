// Windows platform layer.
#if YPLATFORM_WINDOWS
#	include"platform_win32.hpp"

namespace Yazh {
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

	f64 Platform::getAbsoluteTime() {
		LARGE_INTEGER now_time;
		QueryPerformanceCounter(&now_time);
		return (f64)now_time.QuadPart * Platform::clock_frequency;
	}

	void Platform::sleep(u64 ms) {
		Sleep(ms);
	}
}

#endif // KPLATFORM_WINDOWS
