#include"game.hpp"

#include<entry.hpp>

// Define the function to create a game.
namespace Yazh::Game {
	Game game;
	Game* create() {
		// Application configuration.
		game.appConfig.startPosX = 100;
		game.appConfig.startPosY = 100;
		game.appConfig.startWidth = 1280;
		game.appConfig.startHeight = 720;
		game.appConfig.name = (char*)"Yazh Engine Testbed";
		
		return &game;
	}
} // namespace Yazh::Game