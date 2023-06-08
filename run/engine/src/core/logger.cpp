#include"logger.hpp"
#include"asserts.hpp"

/* TODO (#1#): temporary */

namespace Yazh::Logger {
	
	std::ostream& operator<<(std::ostream& os, const log_level& level) {
		switch(level) {
			case log_level::FTL:	os << "FATAL"; return os;
			case log_level::ERR:	os << "ERROR"; return os;
			case log_level::WRN:	os << "WARN "; return os;
			case log_level::INF:	os << "INFO "; return os;
			case log_level::DBG:	os << "DEBUG"; return os;
			case log_level::TRC:	os << "TRACE"; return os;
			default:			return os;
		};
	};
	
	void reportAssertionFailure(std::string expression, std::string message, std::string file, i32 line) {
		logOutput(log_level::FTL, std::string("Assertion failure: "), expression, std::string(", message: '"), message, std::string("', in file: "), file, std::string(", line: "), line, '\n');
	}
	
	b initializeLogging() {
		/* TODO (#1#): create log file. */
		return true;
	}
	
	void shutdownLogging() {
		/* TODO (#1#): cleanup logging/write queued entries. */
	}
} // namespace Yazh::Logger
