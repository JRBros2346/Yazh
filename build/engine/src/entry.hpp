#pragma once

#include"core/application.hpp"
#include"core/logger.hpp"
#include"game_types.hpp"

namespace Yazh {
	namespace Game {
		// Externally defined function to create a Game
		extern b create(GameState* outGame);
	} // namespace Game
	
	/**
	 * The main entry point of the application.
	 */
	int main(void) {
		
		// Request the game instance from the application.
		Game::GameState gameInst;
		if (!Game::create(&gameInst)) {
			YFATAL("Could not create game!");
			return -1;
		}
		
		// Ensure the funtion pointers are defined.
		if (!gameInst.render || !gameInst.update || !gameInst.initialize || !gameInst.onResize) {
			YFATAL("The game's funtion pointers must be defined!");
			return -2;
		}
		
		Application app;
		
		// Initialization.
		if (!app.create(&gameInst)) {
			YINFO("Application failed to create!");
			return 1;
		}
		
		// Begin the game loop.
		if (!app.run()) {
			YINFO("Application did not shutdown gracefully.");
			return 2;
		}
		
		return 0;
	}
} // namespace Yazh