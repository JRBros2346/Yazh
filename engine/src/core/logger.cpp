#include"logger.hpp"
#include"asserts.hpp"

/* TODO (#1#): temporary */

namespace Yazh::Logger {
	void reportAssertionFailure(std::string expression, std::string message, std::string file, i32 line) {
		logOutput(log_level::FATAL, "Assertion failure: ", expression, ", message: '", message, "', in file: ", file, ", line: ", line, '\n');
	}
	
	b initializeLogging() {
		/* TODO (#1#): create log file. */
		return true;
	}
	
	void shutdownLogging() {
		/* TODO (#1#): cleanup logging/write queued entries. */
	}
} // namespace Yazh::Logger
