#pragma once

#include"core/application.hpp"
#include"core/logger.hpp"
#include"game_types.hpp"

namespace Yazh::Game {
	// Externally defined function to create a game.
	extern class Game : public _Game {
		public:
			static Game create();
	};
}

/**
 * The main entry point of the application
 */
int main(void) {
	
	// Request the game instance from the application.
	Game game;
	if(!Game.create()) {
		YFATAL("Could not create game!");
		return -1;
	}
	
	// Ensure the virtual functions are overriden
	if(!game.render || !game.update || !game.initialize || !game.onResize) {
		YFATAL("The game's virtual functions must be overriden!");
		return -2;
	}
	
	// Initialization.
	if (!Yazh::Application::create(&game)) {
		YINFO("Application failed to create!");
		return 1;
	}
	
	// Begin th game loop.
	if(!Yazh::Application::run()) {
		YINFO("Application did not shutdown gracefully.");
		return 2;
	}
	
	return 0;
}
