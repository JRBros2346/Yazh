#include"game.hpp"

#include<core/logger.hpp>

b Game::initialize(Yazh::Game::game gameInst) {
	YDEBUG("Game::initialize() called!");
	return true;
}
b Game::update(Yazh::Game::game gameInst, f32 deltaTime) {
	return true;
}
b Game::render(Yazh::Game::game gameInst, f32 deltaTime) {
	return true;
}
void Game::onResize(Yazh::Game::game gameInst, u32 width, u32 height) {
}