#include"logger.hpp"
#include"asserts.hpp"

/* TODO (#1#): temporary */

namespace yazh::logger {
	void report_assertion_failure(std::string expression, std::string message, std::string file, i32 line) {
		log_output(log_level::FATAL, "Assertion failure: ", expression, ", message: '", message, "', in file: ", file, ", line: ", line, '\n');
	}
	
	b initialize_logging() {
		/* TODO (#1#): create log file. */
		return true;
	}
	
	void shutdown_logging() {
		/* TODO (#1#): cleanup logging/write queued entries. */
	
	}
} // namespace yazh::logger
