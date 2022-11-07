#include"logger.h"

/* TODO (#1#): temporary */
#include<iostream>

b initialize_logging() {
	/* TODO (#1#): create log file. */
	return true;
}
void shutdown_logging() {
	/* TODO (#1#): cleanup logging/write queued entries. */
	
}

template<class ...Args>
YAPI void log_output(log_level level, Args &&...message) {
	const std::string level_strings[6] = {"[FATAL]: ", "[ERROR]: ", "[WARN]: ", "[INFO]: ", "[DEBUG]: ", "[TRACE]: "};
	// b is_error = (int)level < 2;
	
	/* TODO (#1#): platform specific output. */
	(std::clog << level_strings[(int)level] << ... << message) << std::endl;
}