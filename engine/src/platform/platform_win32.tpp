#pragma once

namespace Yazh {
	template<class ...fragments>
	void consoleWrite(Logger::log_level level, fragments&& ...message) {
		// FATAL,ERROR,WARN,INFO,DEBUG,TRACE
		static std::map<Logger::log_level, std::string> colors{
			{Logger::log_level::FTL, "\033[41m"}, 
			{Logger::log_level::ERR, "\033[31m"}, 
			{Logger::log_level::WRN, "\033[33m"}, 
			{Logger::log_level::INF, "\033[32m"}, 
			{Logger::log_level::DBG, "\033[34m"},
			{Logger::log_level::TRC, "\033[37m"}
		};
		(std::clog << colors[level] << "[ " << level << " ]" << "\033[m" << ": " << ... << message) << '\n';
	}

	template<class ...fragments>
	void consoleWriteError(Logger::log_level level, fragments&& ...message) {
		// FATAL,ERROR,WARN,INFO,DEBUG,TRACE
		static std::map<Logger::log_level, std::string> colors{
			{Logger::log_level::FTL, "\033[41m"}, 
			{Logger::log_level::ERR, "\033[31m"}, 
			{Logger::log_level::WRN, "\033[33m"}, 
			{Logger::log_level::INF, "\033[32m"}, 
			{Logger::log_level::DBG, "\033[34m"},
			{Logger::log_level::TRC, "\033[37m"}
		};
		(std::cerr << colors[level] << "[ " << level << " ]" << "\033[m" << ": " << ... << message) << '\n';
	}
} // namespace Yazh