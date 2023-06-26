#pragma once

#include"defines.hpp"
#include"core/application.hpp"
#include"core/logger.hpp"
#include"core/ymemory.hpp"
#include"game_types.hpp"

// Externally defined function to create game.
namespace Yazh {
	Yazh::VirtualGame* createGame();
}

/**
 * The main entry point of the app.
 */
int main(void) {
	
	Yazh::Memory::initialize();
	
	// Request the game instance from the app.
	Yazh::VirtualGame* game = Yazh::createGame();
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
	
	Yazh::Memory::shutdown();
	
	return 0;
}
