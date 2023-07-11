#pragma once
#include<game_types.hpp>

#include<core/logger.hpp>

class Game : public Yazh::Game::VirtualGame {
	f32 deltaTime;
	public:
		bool initialize();
		bool update(f32);
		bool render(f32);
		void onResize(u32, u32);
};