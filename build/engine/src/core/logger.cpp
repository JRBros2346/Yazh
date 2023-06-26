#include"logger.hpp"
#include"asserts.hpp"

/* TODO (#1#): temporary */

namespace Yazh::Logger {
	std::ostream& operator<<(std::ostream& os, const LogLevel& level) {
		// FATAL,ERROR,WARN,INFO,DEBUG,TRACE
		static std::map<LogLevel, std::string> colors{
			{LogLevel::FTL, "\033[41m"}, // Red background 
			{LogLevel::ERR, "\033[31m"}, // Red
			{LogLevel::WRN, "\033[33m"}, // Yellow
			{LogLevel::INF, "\033[32m"}, // Green
			{LogLevel::DBG, "\033[34m"}, // Blue
			{LogLevel::TRC, "\033[37m"}  // White
		};
		
		os << colors[level] << "\033[1m"; // Bold and Underline
		switch(level) {
			case LogLevel::FTL:	os << "[ FATAL ]"; break;
			case LogLevel::ERR:	os << "[ ERROR ]"; break;
			case LogLevel::WRN:	os << "[  WARN ]"; break;
			case LogLevel::INF:	os << "[  INFO ]"; break;
			case LogLevel::DBG:	os << "[ DEBUG ]"; break;
			case LogLevel::TRC:	os << "[ TRACE ]"; break;
			default: return os;
		};
		os << "\033[m";
		return os;
	};
	
	void reportAssertionFailure(std::string expression, std::string message, std::string file, i32 line) {
		logOutput(LogLevel::FTL, std::string("Assertion failure: "), expression, std::string(", message: '"), message, std::string("', in file: "), file, std::string(", line: "), line, '\n');
	}
	
	bool initializeLogging() {
		/* TODO (#1#): create log file. */
		return true;
	}
	
	void shutdownLogging() {
		/* TODO (#1#): cleanup logging/write queued entries. */
	}
} // namespace Yazh::Logger
