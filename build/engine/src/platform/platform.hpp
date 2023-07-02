#pragma once

#include"defines.hpp"

namespace Yazh {
	class VirtualPlatform {
		public:
			virtual bool startup(
				const char* applicationName,
				i32 x,
				i32 y,
				i32 width,
				i32 height) = 0;
			
			virtual void shutdown() = 0;
			
			virtual bool pumpMessages() = 0;
	};
}