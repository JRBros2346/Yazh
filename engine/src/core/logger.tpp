#pragma once

#include<iostream>

#include"platform/platform.hpp"

namespace Yazh::Logger {
	template<class ...fragments>
	void logOutput(log_level level, fragments ...message) {
		auto is_error = (u8)level < (u8)log_level::WRN;
		
		// platform specific output.
		if (is_error)
			consoleWriteError(level, message...);
		else
			consoleWrite(level, message...);
	}
} // namespace Yazh::Logger