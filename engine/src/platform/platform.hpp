#pragma once
#include<memory>
#include<map>

#include"defines.hpp"
#include"core/logger.hpp"

namespace Yazh {
	class _Platform {
		public:
			virtual b startup(
				const char* application_name,
				i32 x,
				i32 y,
				i32 width,
				i32 height) { return true; };
			
			virtual void shutdown() {};
			
			virtual b pumpMessages() { return false; };
			
			virtual void* allocate(u64 size, b aligned) { return malloc(0); };
			virtual void free(void* block, b aligned) {};
			virtual void* zeroMemory(void* block, u64 size) { return block; };
			virtual void* copyMemory(void* dest, const void* source, u64 size) { return dest; };
			virtual void* setMemory(void* dest, i32 value, u64 size) { return dest; };
			
			virtual f64 getAbsoluteTime() { return 0.0f; };
			
			// Sleep on the thread for the provided ms. This blocks the main thread.
			// Should only be used for giving time back to the OS for unused update power.
			// Therefore it is not exported.
			virtual void sleep(u64 ms) {};
	};

	template<class ...fragments>
	YAPI void consoleWrite(Logger::log_level level, fragments&& ...message);
	template<class ...fragments>
	YAPI void consoleWriteError(Logger::log_level level, fragments&& ...message);
} // namespace Yazh
