#pragma once

#include"defines.hpp"
#include<iostream>

namespace Yazh::Core::Logger {
#define LOG_WARN_ENABLED true
#define LOG_INFO_ENABLED true
#define LOG_DEBUG_ENABLED true
#define LOG_TRACE_ENABLED true

#if YRELEASE == 1
#	define LOG_DEBUG_ENABLED false
#	define LOG_TRACE_ENABLED false
#endif

	// FATAL, ERROR, WARN, INFO, DEBUG, TRACE
	enum class LogLevel : u8 {
		FTL,
		ERR,
		WRN,
		INF,
		DBG,
		TRC
	};
	static const u8 colors[6] = { 41, 31, 33, 32, 34, 37 };
	static const char strings[6][6] = { "FATAL", "ERROR", "WARN", "INFO", "DEBUG", "TRACE" };

	// YAPI std::ostream& operator<<(std::ostream&, const LogLevel&);

	bool initialize();
	void shutdown();

	template<typename... Args>
	constexpr void logOutput(LogLevel, std::string, Args&&...);

	template<typename... Args>
	constexpr void Fatal(std::string, Args&&...);
	template<typename... Args>
	constexpr void Error(std::string, Args&&...);
	template<typename... Args>
	constexpr void Warn(std::string, Args&&...);
	template<typename... Args>
	constexpr void Info(std::string, Args&&...);
	template<typename... Args>
	constexpr void Debug(std::string, Args&&...);
	template<typename... Args>
	constexpr void Trace(std::string, Args&&...);
} // namespace Yazh::Core::Logger

namespace Yazh {
	using Core::Logger::Fatal;
	using Core::Logger::Error;
	using Core::Logger::Warn;
	using Core::Logger::Info;
	using Core::Logger::Debug;
	using Core::Logger::Trace;
} // namespace Yazh

#include"logger.tcc"
