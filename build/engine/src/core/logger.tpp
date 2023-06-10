#pragma once

#include"platform/platform.hpp"
#include"platform/platform.tpp"

namespace Yazh::Logger {
	template<class ...fragments>
	void logOutput(log_level level, fragments&& ...message) {
		auto is_error = level < log_level::WRN;
		
		// platform specific output.
		if (is_error)
			consoleWriteError(level, message...);
		else
			consoleWrite(level, message...);
	}
} // namespace Yazh::Logger
