#pragma once

#include<defines.hpp>
#include<game_types.hpp>

class Game {
	f32 deltaTime;
	public:
		b initialize(Yazh::Game::game);
		b update(Yazh::Game::game, f32);
		b render(Yazh::Game::game, f32);
		b onResize(Yazh::Game::game, u32, u32);
		
};