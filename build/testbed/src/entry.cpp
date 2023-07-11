#include"game.hpp"

#include<entry.hpp>

Game game;
// Define the function to create a game.
Yazh::Game::VirtualGame* Yazh::Game::createGame() {
	// Application configuration.
	game.app_config.start_pos_x = 100;
	game.app_config.start_pos_y = 100;
	game.app_config.start_width = 1280;
	game.app_config.start_height = 720;
	game.app_config.name = (char*)"Yazh Engine Testbed";
	
	return &game;
}
