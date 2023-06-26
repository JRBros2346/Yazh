#pragma once

#include<map>

namespace Yazh::Logger {
	template<class ...fragments>
	void logOutput(LogLevel level, fragments&& ...message) {
		auto is_error = level < LogLevel::WRN;
		
		if (is_error)
			(std::cerr << level << ": " << ... << message) << '\n';
		else
			(std::clog << level << ": " << ... << message) << '\n';
	}
} // namespace Yazh::Logger
