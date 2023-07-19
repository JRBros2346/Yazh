#include"logger.hpp"
#include"asserts.hpp"

namespace Yazh::Core::Logger {
	std::ostream& operator<<(std::ostream& os, const LogLevel& level) {
		os << colors[(ysize)level] << "\033[1m"; // Bold
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
	
	constexpr void reportAssertionFailure(std::string expression, std::string message, std::string file, i32 line) {
		logOutput(LogLevel::FTL, "Assertion failure: {}, message: '{}', in file: {}, line: {}", expression, message, file, line);
	}
	
	bool initialize() {
		// TODO: create log file.
		return true;
	}
	
	void shutdown() {
		// TODO: cleanup logging/write queued entries.
	}
} // namespace Yazh::Core::Logger
