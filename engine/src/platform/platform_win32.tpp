#pragma once

namespace Yazh {
	template<class ...fragments>
	void consoleWrite(Logger::log_level level, const fragments &&...message) {
		// FATAL,ERROR,WARN,INFO,DEBUG,TRACE
		// const static std::string level_strings[6] = {"FATAL", "ERROR", "WARN ", "INFO ", "DEBUG", "TRACE"};
		const std::map<Logger::log_level, std::string> level_strings{{Logger::log_level::FTL, "FATAL"},{Logger::log_level::ERR, "ERROR"},{Logger::log_level::WRN, "WARN "},{Logger::log_level::INF, "INFO "},{Logger::log_level::DBG, "DEBUG"},{Logger::log_level::TRC, "TRACE"}};
		// static u8 levels[6] = {64, 4, 6, 2, 1, 8};
		(std::clog << "[ " << level_strings[level] << " ]: " << ... << message) << '\n';
	}

	template<class ...fragments>
	void consoleWriteError(Logger::log_level level, const fragments &&...message) {
		// FATAL,ERROR,WARN,INFO,DEBUG,TRACE
		const std::map<Logger::log_level, std::string> level_strings{{Logger::log_level::FTL, "FATAL"},{Logger::log_level::ERR, "ERROR"},{Logger::log_level::WRN, "WARN "},{Logger::log_level::INF, "INFO "},{Logger::log_level::DBG, "DEBUG"},{Logger::log_level::TRC, "TRACE"}};
		// static u8 levels[6] = {64, 4, 6, 2, 1, 8};
		(std::cerr << "[ " << level_strings[level] << " ]: " << ... << message) << '\n';
	}
} // namespace Yazh