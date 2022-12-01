#pragma once
#include<memory>

#include"defines.hpp"

namespace Yazh {
	class Platform {
		struct state;
		std::unique_ptr<state> pimpl;
		public:
			Platform();
			~Platform();
			b startup(
				const std::string application_name,
				i32 x,
				i32 y,
				i32 width,
				i32 height);
			
			shutdown();
			
			b pumpMessages();
			
			std::unique_ptr<void> allocate(u64 size, b aligned);
			void free(std::unique_ptr<void> block, b aligned);
			std::unique_ptr<void> zeroMemory(std::unique_ptr<void> block, u64 size);
			std::unique_ptr<void> copyMemory(std::unique_ptr<void> dest, const std::unique_ptr<void> source, u64 size);
			std::unique_ptr<void> setMemory(std::unique_ptr<void> dest, i32 value, u64 size);
			
			f64 getAbsoluteTime();
			
			// Sleep on the thread for the provided ms. This blocks the main thread.
			// Should only be used for giving time back to the OS for unused update power.
			// Therefore it is not exported.
			void sleep(u64 ms);
	};
	
	void consoleWrite(const std::string message, u8 color);
	void consoleWriteError(const std::string message, u8 color);
	
} // namespace Yazh