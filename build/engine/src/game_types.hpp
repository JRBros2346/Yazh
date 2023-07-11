#pragma once

#include"defines.hpp"
#include"core/application.hpp"

namespace Yazh::Game {
	class VirtualGame {
		public:
			Application::config app_config;
			
			virtual bool initialize() = 0;
			virtual bool update(f32) = 0;
			virtual bool render(f32) = 0;
			virtual void onResize(u32, u32) = 0;
	};
} // namespace Yazh::Game