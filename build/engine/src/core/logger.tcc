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

	// Logs a fatal-level message.
	template<typename... Fragment>
	void Fatal(Fragment&&... message) {
		Yazh::Logger::logOutput(Yazh::Logger::LogLevel::FTL, std::forward<Fragment>(message)...);
	}

#ifndef YERROR
#	define YERROR
	// Logs an error-level message.
	template<typename... Fragment>
	void Error(Fragment&&... message) {
		Yazh::Logger::logOutput(Yazh::Logger::LogLevel::ERR, std::forward<Fragment>(message)...);
	}
#endif

#if LOG_WARN_ENABLED
	// Logs a warning-level message.
	template<typename... Fragment>
	void Warn(Fragment&&... message) {
		Yazh::Logger::logOutput(Yazh::Logger::LogLevel::WRN, std::forward<Fragment>(message)...);
	}
#else
	// Does nothing when LOG_WARN_ENABLED != true
	template<typename... Fragment>
	void Warn(Fragment&&... message) {}
#endif

#if LOG_INFO_ENABLED
	// Logs a info-level message.
	template<typename... Fragment>
	void Info(Fragment&&... message) {
		Yazh::Logger::logOutput(Yazh::Logger::LogLevel::INF, std::forward<Fragment>(message)...);
	}
#else
	// Does nothing when LOG_INFO_ENABLED != true
	template<typename... Fragment>
	void Info(Fragment&&... message) {}
#endif

#if LOG_DEBUG_ENABLED
	// Logs a debug-level message.
	template<typename... Fragment>
	void Debug(Fragment&&... message) {
		Yazh::Logger::logOutput(Yazh::Logger::LogLevel::DBG, std::forward<Fragment>(message)...);
	}
#else
	// Does nothing when LOG_DEBUG_ENABLED != true
	template<typename... Fragment>
	void Debug(Fragment&&... message) {}
#endif

#if LOG_TRACE_ENABLED
	// Logs a trace-level message.
	template<typename... Fragment>
	void Trace(Fragment&&... message) {
		Yazh::Logger::logOutput(Yazh::Logger::LogLevel::TRC, std::forward<Fragment>(message)...);
	}
#else
	// Does nothing when LOG_TRACE_ENABLED != true
	template<typename... Fragment>
	void Trace(Fragment&&... message) {}
#endif
} // namespace Yazh::Logger
