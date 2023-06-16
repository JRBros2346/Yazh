#pragma once
#include<game_types.hpp>

namespace Yazh::Game {
	class Game : public _Game {
		f32 deltaTime
		public:
			bool initialize() override {
				YDEBUG("Yazh::Game::Game::initialize() called!");
				return true;
			}
			bool update(f32 deltaTime) {
				return true;
			}
			bool render(f32 deltaTime) {
				return true;
			}
			void onResize(u32 width, u32 height) {
			}
	};
} // namespace Lib::Game