#pragma once

namespace Yazh::Logger {
	template<typename... Fragment>
	void logOutput(LogLevel level, Fragment&&... message) {
		auto is_error = level < LogLevel::WRN;
		
		if (is_error)
			(std::cerr << level << ": " << colors[(ysize)level] << "\033[4m" << ... << std::forward<Fragment>(message)) << "\033[m\n"; // Underlined
		else
			(std::clog << level << ": " << colors[(ysize)level] << ... << std::forward<Fragment>(message)) << "\033[m\n";
	}
} // namespace Yazh::Logger
