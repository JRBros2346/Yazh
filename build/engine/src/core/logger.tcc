#pragma once

#include<format>

namespace Yazh::Core::Logger {
	template<typename... Args>
	constexpr void logOutput(LogLevel level, std::string fmt, Args&&... args) {
		auto is_error = level < LogLevel::WRN;
		
		if (is_error)
			std::cerr << std::format("\033[{0};1m[ {1:>5} ]\033[m: \033[{0};4m{2}\033[m", colors[static_cast<u8>(level)], strings[static_cast<u8>(level)], std::vformat(fmt, std::make_format_args(std::forward<Args>(args)...))) << std::endl; // Underlined
		else
			std::clog << std::format("\033[{0};1m[ {1:>5} ]\033[m: \033[{0}m{2}\033[m", colors[static_cast<u8>(level)], strings[static_cast<u8>(level)], std::vformat(fmt, std::make_format_args(std::forward<Args>(args)...))) << std::endl;
	}

	// Logs a fatal-level message.
	template<typename... Args>
	constexpr void Fatal(std::string fmt, Args&&... args) {
		logOutput(LogLevel::FTL, fmt, std::forward<Args>(args)...);
	}

#ifndef YERROR
#	define YERROR
	// Logs an error-level message.
	template<typename... Args>
	constexpr void Error(std::string fmt, Args&&... args) {
		logOutput(LogLevel::ERR, fmt, std::forward<Args>(args)...);
	}
#endif

#if LOG_WARN_ENABLED
	// Logs a warning-level message.
	template<typename... Args>
	constexpr void Warn(std::string fmt, Args&&... args) {
		logOutput(LogLevel::WRN, fmt, std::forward<Args>(args)...);
	}
#else
	// Does nothing when LOG_WARN_ENABLED != true
	template<typename... Args>
	constexpr void Warn(std::string fmt, Args&&... args) {}
#endif

#if LOG_INFO_ENABLED
	// Logs a info-level message.
	template<typename... Args>
	constexpr void Info(std::string fmt, Args&&... args) {
		logOutput(LogLevel::INF, fmt, std::forward<Args>(args)...);
	}
#else
	// Does nothing when LOG_INFO_ENABLED != true
	template<typename... Args>
	constexpr void Info(std::string fmt, Args&&... args) {}
#endif

#if LOG_DEBUG_ENABLED
	// Logs a debug-level message.
	template<typename... Args>
	constexpr void Debug(std::string fmt, Args&&... args) {
		logOutput(LogLevel::DBG, fmt, std::forward<Args>(args)...);
	}
#else
	// Does nothing when LOG_DEBUG_ENABLED != true
	template<typename... Args>
	constexpr void Debug(std::string fmt, Args&&... args) {}
#endif

#if LOG_TRACE_ENABLED
	// Logs a trace-level message.
	template<typename... Args>
	constexpr void Trace(std::string fmt, Args&&... args) {
		logOutput(LogLevel::TRC, fmt, std::forward<Args>(args)...);
	}
#else
	// Does nothing when LOG_TRACE_ENABLED != true
	template<typename... Args>
	constexpr void Trace(std::string fmt, Args&&... args) {}
#endif
} // namespace Yazh::Core::Logger
