// Linux Platform Layer
#if YPLATFORM_LINUX
#	include"platform_linux.hpp"

namespace Yazh {

	void* Platform::allocate(u64 size, bool aligned) {
		return malloc(size);
	}

	void Platform::free(void *block, bool aligned) {
		::free(block);
	}

	void* Platform::zeroMemory(void *block, u64 size) {
		return memset(block, 0, size);
	}

	void* Platform::copyMemory(void *dest, const void* source, u64 size) {
		return memcpy(dest, source, size);
	}

	void* Platform::setMemory(void *dest, i32 value, u64 size) {
		return memset(dest, value, size);
	}

	f64 Platform::getAbsoluteTime() {
		struct timespec now;
		clock_gettime(CLOCK_MONOTONIC, &now);
		return now.tv_sec + now.tv_nsec * 0.000000001;
	}

	void Platform::sleep(u64 ms) {
		std::this_thread::sleep_for(std::chrono::milliseconds(ms));
	}
} // namespace Yazh

#endif // YPLATFORM_LINUX
