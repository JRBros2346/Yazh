#include"game.hpp"
#include<entry.hpp>

Game Yazh::Game::Game::create() {
	
	Game game;
	// Application configuration.
	game.appConfig.startPosX = 100;
	game.appConfig.startPosY = 100;
	game.appConfig.startWidth = 1280;
	game.appConfig.startHeight = 720;
	game.appConfig.name = (char*)"Yazh Engine Testbed";
	
	return game;
}