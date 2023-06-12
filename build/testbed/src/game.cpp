#include"game.hpp"

#include<core/logger.hpp>
	
b Game::initialize(Yazh::Game::GameState gameInst) {
	YDEBUG("Game::initialize() called!");
	return true;
}
b Game::update(Yazh::Game::GameState gameInst, f32 deltaTime) {
	return true;
}
b Game::render(Yazh::Game::GameState gameInst, f32 deltaTime) {
	return true;
}
void Game::onResize(Yazh::Game::GameState gameInst, u32 width, u32 height) {
}