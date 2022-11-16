#pragma once
#include<iostream>

namespace Yazh::Logger {
	template<class ...fragments>
	void logOutput(log_level level, fragments &&...message) {
		const std::string level_strings[6] = {"[ FATAL ]: ", "[ ERROR ]: ", "[ WARN  ]: ", "[ INFO  ]: ", "[ DEBUG ]: ", "[ TRACE ]: "};
		auto is_error = (int)level < 2;
		
		/* TODO (#1#): platform specific output. */
		if (is_error) {
			(std::cerr << level_strings[(int)level] << ... << message) << '\n';
		} else {
			(std::clog << level_strings[(int)level] << ... << message) << '\n';
		}
	}
} // namespace Yazh::Logger