#pragma once
#include<iostream>

namespace yazh::logger {
	template<class ...Args>
	YAPI void log_output(log_level level, Args &&...message) {
		const std::string level_strings[6] = {"[FATAL]: ", "[ERROR]: ", "[WARN]: ", "[INFO]: ", "[DEBUG]: ", "[TRACE]: "};
		// b is_error = (int)level < 2;

		/* TODO (#1#): platform specific output. */
		(std::clog << level_strings[(int)level] << ... << message) << std::endl;
	}
} // namespace yazh::logger