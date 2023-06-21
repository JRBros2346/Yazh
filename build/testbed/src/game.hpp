#pragma once
#include<game_types.hpp>

#include<core/logger.hpp>

class Game : public Yazh::VirtualGame {
	f32 deltaTime;
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