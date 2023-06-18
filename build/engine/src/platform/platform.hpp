#pragma once

#include"defines.hpp"
#include<thread>

namespace Yazh {
	class VirtualPlatform {
		public:
			virtual bool startup(
				const char* applicationName,
				i32 x,
				i32 y,
				i32 width,
				i32 height) { return false; };
			
			virtual void shutdown() {};
			
			virtual bool pumpMessages() { return false; };
	};
}