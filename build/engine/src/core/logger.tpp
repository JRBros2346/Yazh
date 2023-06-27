#pragma once

#include<map>

namespace Yazh::Logger {
	template<class ...fragments>
	void logOutput(LogLevel level, fragments&& ...message) {
		auto isError = level < LogLevel::WRN;
		
		// FATAL,ERROR,WARN,INFO,DEBUG,TRACE
		static std::map<LogLevel, std::string> colors{
			{LogLevel::FTL, "\033[41m"}, // Red Background 
			{LogLevel::ERR, "\033[31m"}, // Red
			{LogLevel::WRN, "\033[33m"}, // Yellow
			{LogLevel::INF, "\033[32m"}, // Green
			{LogLevel::DBG, "\033[34m"}, // Blue
			{LogLevel::TRC, "\033[37m"}  // White
		};
		
		if (isError)
			(std::cerr << level << ": " << colors[level] << "\033[4m" << ... << message) << "\033[m\n"; // Underlined
		else
			(std::clog << level << ": " << colors[level] << ... << message) << "\033[m\n";
	}
} // namespace Yazh::Logger
