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
	
	enum class log_level {
		FTL, 
		ERR, 
		WRN, 
		INF, 
		DBG, 
		TRC
	};
	std::ostream& operator<<(std::ostream&, const log_level&);
	
	b initializeLogging();
	void shutdownLogging();
	
	template<class ...fragments>
	YAPI void logOutput(log_level level, fragments&& ...message);
} // namespace Yazh::Logger

// Logs a fatal-level message.
#define YFATAL(message...) Yazh::Logger::logOutput(Yazh::Logger::log_level::FTL, ##message);

#ifndef YERROR
// Logs an error-level message.
#	define YERROR(message...) Yazh::Logger::logOutput(Yazh::Logger::log_level::ERR, ##message);
#endif

#if LOG_WARN_ENABLED
// Logs a warning-level message.
#	define YWARN(message...) Yazh::Logger::logOutput(Yazh::Logger::log_level::WRN, ##message);
#else
// Does nothing when LOG_WARN_ENABLED != true
#	define YWARN(message...)
#endif

#if LOG_INFO_ENABLED
// Logs a info-level message.
#	define YINFO(message...) Yazh::Logger::logOutput(Yazh::Logger::log_level::INF, ##message);
#else
// Does nothing when LOG_INFO_ENABLED != true
#	define YINFO(message...)
#endif

#if LOG_DEBUG_ENABLED
// Logs a debug-level message.
#	define YDEBUG(message...) Yazh::Logger::logOutput(Yazh::Logger::log_level::DBG, ##message);
#else
// Does nothing when LOG_DEBUG_ENABLED != true
#	define YDEBUG(message...)
#endif

#if LOG_TRACE_ENABLED
// Logs a trace-level message.
#	define YTRACE(message...) Yazh::Logger::logOutput(Yazh::Logger::log_level::TRC, ##message);
#else
// Does nothing when LOG_TRACE_ENABLED != true
#	define YTRACE(message...)
#endif

#include"logger.tpp"