#pragma once

#include"defines.hpp"

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
		FATAL, 
		ERROR, 
		WARN, 
		INFO, 
		DEBUG, 
		TRACE
	};
	
	b initializeLogging();
	void shutdownLogging();
	
	template<class ...fragments>
	YAPI void logOutput(log_level level, fragments &&...message);
} // namespace Yazh::Logger

// Logs a fatal-level message.
#define YFATAL(message...) Yazh::Logger::logOutput(Yazh::Logger::log_level::FATAL, ##message);

#ifndef YERROR
// Logs an error-level message.
#	define YERROR(message...) Yazh::Logger::logOutput(Yazh::Logger::log_level::ERROR, ##message);
#endif

#if LOG_WARN_ENABLED
// Logs a warning-level message.
#	define YWARN(message...) Yazh::Logger::logOutput(Yazh::Logger::log_level::WARN, ##message);
#else
// Does nothing when LOG_WARN_ENABLED != true
#	define YWARN(message...)
#endif

#if LOG_INFO_ENABLED
// Logs a info-level message.
#	define YINFO(message...) Yazh::Logger::logOutput(Yazh::Logger::log_level::INFO, ##message);
#else
// Does nothing when LOG_INFO_ENABLED != true
#	define YINFO(message...)
#endif

#if LOG_DEBUG_ENABLED
// Logs a debug-level message.
#	define YDEBUG(message...) Yazh::Logger::logOutput(Yazh::Logger::log_level::DEBUG, ##message);
#else
// Does nothing when LOG_DEBUG_ENABLED != true
#	define YDEBUG(message...)
#endif

#if LOG_TRACE_ENABLED
// Logs a trace-level message.
#	define YTRACE(message...) Yazh::Logger::logOutput(Yazh::Logger::log_level::TRACE, ##message);
#else
// Does nothing when LOG_TRACE_ENABLED != true
#	define YTRACE(message...)
#endif

#include"logger.tpp"