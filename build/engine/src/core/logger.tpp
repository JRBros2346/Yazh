#pragma once

#include<map>

namespace Yazh::Logger {
	template<class ...fragments>
	void logOutput(LogLevel level, fragments&& ...message) {
		auto is_error = level < LogLevel::WRN;
		
		// FATAL,ERROR,WARN,INFO,DEBUG,TRACE
		static std::map<LogLevel, std::string> colors{
			{LogLevel::FTL, "\033[41m"}, 
			{LogLevel::ERR, "\033[31m"}, 
			{LogLevel::WRN, "\033[33m"}, 
			{LogLevel::INF, "\033[32m"}, 
			{LogLevel::DBG, "\033[34m"},
			{LogLevel::TRC, "\033[37m"}
		};
		
		// platform specific output.
		if (is_error) {
			(std::cerr << colors[level] << "[ " << level << " ]" << "\033[m" << ": " << ... << message) << '\n';
		} else {
			(std::clog << colors[level] << "[ " << level << " ]" << "\033[m" << ": " << ... << message) << '\n';
		}
	}
} // namespace Yazh::Logger
