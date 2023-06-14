#include"logger.hpp"
#include"asserts.hpp"

/* TODO (#1#): temporary */

namespace Yazh::Logger {
	
	std::ostream& operator<<(std::ostream& os, const LogLevel& level) {
		switch(level) {
			case LogLevel::FTL:	os << "FATAL"; return os;
			case LogLevel::ERR:	os << "ERROR"; return os;
			case LogLevel::WRN:	os << " WARN"; return os;
			case LogLevel::INF:	os << " INFO"; return os;
			case LogLevel::DBG:	os << "DEBUG"; return os;
			case LogLevel::TRC:	os << "TRACE"; return os;
			default:			return os;
		};
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
