#pragma once

#include"defines.hpp"

namespace Yazh {
	class VirtualPlatform {
		public:
			virtual bool startup(
				const char*,
				i32,
				i32,
				i32,
				i32) = 0;

			virtual void shutdown() = 0;

			virtual bool pumpMessages() = 0;
	};
}
