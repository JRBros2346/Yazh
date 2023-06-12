#include"game.hpp"

#include<entry.hpp>

b Yazh::Game::create(Yazh::Game::GameState* outGame) {
	
	// Application configuration.
	outGame->appConfig.startPosX = 100;
	outGame->appConfig.startPosY = 100;
	outGame->appConfig.startWidth = 1280;
	outGame->appConfig.startHeight = 720;
	outGame->appConfig.name = (char*)"Yazh Engine Testbed";
	
	return true;
}