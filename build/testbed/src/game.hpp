#pragma once

#include<defines.hpp>
#include<game_types.hpp>

class Game {
	f32 deltaTime;
	public:
		b initialize(Yazh::Game::GameState);
		b update(Yazh::Game::GameState, f32);
		b render(Yazh::Game::GameState, f32);
		void onResize(Yazh::Game::GameState, u32, u32);
		
};