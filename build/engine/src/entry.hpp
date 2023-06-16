#pragma once

#include"defines.hpp"
#include"core/application.hpp"
#include"game_types.hpp"

// Externally defined function to create game.
namespace Yazh::Game {
	extern Game* create();
}
/**
 * The main entry point of the app.
 */
int main(void) {
	
	// Request the game instance from the app.
	Yazh::Game::Game* game = Yazh::Game::create();
	if (!game) {
		YFATAL("Could not create game!");
		return -1;
	}
	
	// Ensure the virtual functions are overriden.
	if (!game->render || !game->update || !game->initialize || !game->onResize) {
		YFATAL("The game's virtual functions must be overriden.");
		return -2;
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
