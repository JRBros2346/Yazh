#pragma once

namespace Yazh::Logger {
	template<class ...fragments>
	void logOutput(log_level level, fragments&& ...message) {
		auto is_error = level < log_level::WRN;
		
		// FATAL,ERROR,WARN,INFO,DEBUG,TRACE
		static std::map<log_level, std::string> colors{
			{log_level::FTL, "\033[41m"}, 
			{log_level::ERR, "\033[31m"}, 
			{log_level::WRN, "\033[33m"}, 
			{log_level::INF, "\033[32m"}, 
			{log_level::DBG, "\033[34m"},
			{log_level::TRC, "\033[37m"}
		};
		
		// platform specific output.
		if (is_error) {
			(std::cerr << colors[level] << "[ " << level << " ]" << "\033[m" << ": " << ... << message) << '\n';
		} else {
			(std::clog << colors[level] << "[ " << level << " ]" << "\033[m" << ": " << ... << message) << '\n';
		}
	}
} // namespace Yazh::Logger
