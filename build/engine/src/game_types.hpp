#pragma once

#include"defines.hpp"
#include"core/application.hpp"

namespace Yazh {
	class VirtualGame {
		public:
			Yazh::Application::config appConfig;
			
			virtual bool initialize() = 0;
			virtual bool update(f32) = 0;
			virtual bool render(f32) = 0;
			virtual void onResize(u32, u32) = 0;
	};
}