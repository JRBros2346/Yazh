#include"platform.hpp"

#include"platform_win32.hpp"
#include"platform_linux.hpp"

#include<cmath>

namespace Yazh {
	f64 Platform::getAbsoluteTime() {
		return std::chrono::steady_clock::now().time_since_epoch() / std::chrono::seconds(1);
	}
	void sleep(u64 ms) {
		std::this_thread::sleep_for(std::chrono::milliseconds(ms));
	}
}