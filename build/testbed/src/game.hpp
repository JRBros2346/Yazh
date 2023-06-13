#pragma once

#include<defines.hpp>
#include<game_types.hpp>

class Yazh::Game::Game : public Yazh::Game::GameState {
	f32 deltaTime;
	public:
		b initialize();
		b update(f32);
		b render(f32);
		void onResize(u32, u32);
		
};