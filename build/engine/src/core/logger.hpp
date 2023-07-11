#pragma once

#include"defines.hpp"
#include<iostream>

namespace Yazh::Logger {
#define LOG_WARN_ENABLED true
#define LOG_INFO_ENABLED true
#define LOG_DEBUG_ENABLED true
#define LOG_TRACE_ENABLED true

#if YRELEASE == 1
#	define LOG_DEBUG_ENABLED false
#	define LOG_TRACE_ENABLED false
#endif

	// FATAL, ERROR, WARN, INFO, DEBUG, TRACE
	enum class LogLevel {
		FTL,
		ERR,
		WRN,
		INF,
		DBG,
		TRC
	};
	static const char colors[6][6] = {
		"\033[41m", // Red Background 
		"\033[31m", // Red
		"\033[33m", // Yellow
		"\033[32m", // Green
		"\033[34m", // Blue
		"\033[37m"  // White
	};
	YAPI std::ostream& operator<<(std::ostream&, const LogLevel&);

	bool initialize();
	void shutdown();

	template<typename... Fragment>
	void logOutput(LogLevel, Fragment&&...);
} // namespace Yazh::Logger

// Logs a fatal-level message.
#define YFATAL(message...) Yazh::Logger::logOutput(Yazh::Logger::LogLevel::FTL, ##message);

#ifndef YERROR
// Logs an error-level message.
#	define YERROR(message...) Yazh::Logger::logOutput(Yazh::Logger::LogLevel::ERR, ##message);
#endif

#if LOG_WARN_ENABLED
// Logs a warning-level message.
#	define YWARN(message...) Yazh::Logger::logOutput(Yazh::Logger::LogLevel::WRN, ##message);
#else
// Does nothing when LOG_WARN_ENABLED != true
#	define YWARN(message...)
#endif

#if LOG_INFO_ENABLED
// Logs a info-level message.
#	define YINFO(message...) Yazh::Logger::logOutput(Yazh::Logger::LogLevel::INF, ##message);
#else
// Does nothing when LOG_INFO_ENABLED != true
#	define YINFO(message...)
#endif

#if LOG_DEBUG_ENABLED
// Logs a debug-level message.
#	define YDEBUG(message...) Yazh::Logger::logOutput(Yazh::Logger::LogLevel::DBG, ##message);
#else
// Does nothing when LOG_DEBUG_ENABLED != true
#	define YDEBUG(message...)
#endif

#if LOG_TRACE_ENABLED
// Logs a trace-level message.
#	define YTRACE(message...) Yazh::Logger::logOutput(Yazh::Logger::LogLevel::TRC, ##message);
#else
// Does nothing when LOG_TRACE_ENABLED != true
#	define YTRACE(message...)
#endif

#include"logger.tcc"
