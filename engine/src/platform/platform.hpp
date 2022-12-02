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
			
			void *allocate(u64 size, b aligned);
			void free(void *block, b aligned);
			void *zeroMemory(void *block, u64 size);
			void *copyMemory(void *dest, const void *source, u64 size);
			void *setMemory(void *dest, i32 value, u64 size);
			
			f64 getAbsoluteTime();
			
			// Sleep on the thread for the provided ms. This blocks the main thread.
			// Should only be used for giving time back to the OS for unused update power.
			// Therefore it is not exported.
			void sleep(u64 ms);
	};
	
	void consoleWrite(const std::string message, u8 color);
	void consoleWriteError(const std::string message, u8 color);
	
} // namespace Yazh