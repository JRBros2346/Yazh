#pragma once

#include<defines.hpp>
#include<core/loggers.hpp>
#include<game_types.hpp>

class Yazh::Game::Game : public Yazh::Game::_Game {
	f32 deltaTime
	public:
		bool initialize() override {
			YDEBUG("Yazh::Game::Game::initialize() called!");
			return true;
		}
		bool update(f32 deltaTime) override {
			return true;
		}
		bool render(f32 deltaTime) override {
			return true;
		}
		void onResize(u32 width, u32 height) override {
		}
};