#include"platform.hpp"

#if YPLATFORM_WINDOWS
#	include"platform_win32.hpp"
#elif YPLATFORM_LINUX
#	include"platform_linux.hpp"
#endif

namespace Yazh {
	f64 Platform::getAbsoluteTime() {
		return std::chrono::steady_clock::now().time_since_epoch() / std::chrono::seconds(1);
	}
	void sleep(u64 ms) {
		std::this_thread::sleep_for(std::chrono::milliseconds(ms));
	}
}