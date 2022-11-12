#pragma once
#include<iostream>

namespace yazh::logger {
	template<class ...fragments>
	void log_output(log_level level, fragments &&...message) {
		const std::string level_strings[6] = {"[FATAL]: ", "[ERROR]: ", "[WARN]: ", "[INFO]: ", "[DEBUG]: ", "[TRACE]: "};
		b is_error = (int)level < 2;
		
		/* TODO (#1#): platform specific output. */
		if (is_error) {
			(std::cerr << level_strings[(int)level] << ... << message) << '\n';
		} else {
			(std::clog << level_strings[(int)level] << ... << message) << '\n';
		}
	}
} // namespace yazh::logger