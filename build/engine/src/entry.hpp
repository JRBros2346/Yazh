#pragma once

#include"defines.hpp"
#include"core/application.hpp"
#include"game_types.hpp"

// Externally defined function to create game.
namespace Yazh::Game {
	extern _Game* create();
}
/**
 * The main entry point of the app.
 */
int main(void) {
	
	// Request the game instance from the app.
	Yazh::Game::_Game* game = Yazh::Game::create();
	if (!game) {
		YFATAL("Could not create game!");
		return -1;
	}
	
	// Initialization
	if (!Yazh::Application::create(game)) {
		YINFO("Application failed to create!");
		return 1;
	}
	
	// Begin the game loop.
	if (!Yazh::Application::run()) {
		YINFO("Application did not shutdown gracefully");
		return 2;
	}
	
	return 0;
}
