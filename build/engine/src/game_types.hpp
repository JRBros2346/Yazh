#pragma once

#include"defines.hpp"
#include"core/application.hpp"

namespace Yazh::Game {
	class _Game {
		public:
			Yazh::Application::config appConfig;
			
			virtual bool initialize() = 0;
			virtual bool update(f32 deltaTime) = 0;
			virtual bool render(f32 deltaTime) = 0;
			virtual void onResize(u32 width, u32 height) = 0;
	};
}