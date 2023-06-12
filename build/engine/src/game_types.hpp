#pragma once

#include"core/application.hpp"

/**
 * Represents the basic game state in a game.
 * Called for creation by the application.
 */
namespace Yazh::Game {
	struct game {
		// The application configuration
		Application::config appConfig;
		
		// Function pointer to game's initialize function.
		b (*_initialize)(game* gameInit);
		
		// Function pointer to game's update function.
		b (*_update)(game* gameInit, f32 deltaTime);
		
		// Function pointer to game's render function.
		b (*_render)(game* gameInit, f32 deltaTime);
		
		// Function pointer to handle resizes. If applicable.
		void (*_onResize)(game* gameInit, u32 width, u32 height);
		
//		// Game-specific game state. Created and managed by the game
//		void* state;
	};
} // namespace Yazh