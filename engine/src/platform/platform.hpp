#pragma once
#include<memory>

#include"defines.hpp"

namespace Yazh {
	class _Platform {
		public:
			virtual b startup(
				const char *application_name,
				i32 x,
				i32 y,
				i32 width,
				i32 height);
			
			virtual void shutdown();
			
			virtual b pumpMessages();
			
			virtual void *allocate(u64 size, b aligned);
			virtual void free(void *block, b aligned);
			virtual void *zeroMemory(void *block, u64 size);
			virtual void *copyMemory(void *dest, const void *source, u64 size);
			virtual void *setMemory(void *dest, i32 value, u64 size);
			
			virtual f64 getAbsoluteTime();
			
			// Sleep on the thread for the provided ms. This blocks the main thread.
			// Should only be used for giving time back to the OS for unused update power.
			// Therefore it is not exported.
			virtual void sleep(u64 ms);
			
			virtual ~_Platform();
	};
	_Platform::~_Platform() = default;
	
	
} // namespace Yazh