#pragma once

#include"platform/platform.hpp"

#include<sstream>

namespace Yazh::Logger {
	template<class ...fragments>
	void logOutput(log_level level, fragments &&...message) {
		const std::string level_strings[6] = {"[ FATAL ]: ", "[ ERROR ]: ", "[ WARN  ]: ", "[ INFO  ]: ", "[ DEBUG ]: ", "[ TRACE ]: "};
		auto is_error = (u8)level < (u8)log_level::WARN;
		
		std::stringstream buffer;
		std::string outmessage;
		(buffer << level_strings[(u8)level] << ... << message) << '\n';
		buffer >> outmessage;
		
		// platform specific output.
		if (is_error) {
			consoleWriteError(outmessage, (u8)level);
		} else {
			consoleWrite(outmessage, (u8)level);
		}
	}
} // namespace Yazh::Logger