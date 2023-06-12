#pragma once

#include"core/application.hpp"

/**
 * Represents the basic game state in a game.
 * Called for creation by the application.
 */
namespace Yazh::Game {
	class GameState {
		public:
			// The application configuration
			Yazh::Application::config appConfig;
			
			// Function pointer to game's initialize function.
			b (*initialize)(GameState* gameInit);
			
			// Function pointer to game's update function.
			b (*update)(GameState* gameInit, f32 deltaTime);
			
			// Function pointer to game's render function.
			b (*render)(GameState* gameInit, f32 deltaTime);
			
			// Function pointer to handle resizes. If applicable.
			void (*onResize)(GameState* gameInit, u32 width, u32 height);
			
//			// Game-specific game state. Created and managed by the game
//			void* state;
	};
} // namespace Yazh