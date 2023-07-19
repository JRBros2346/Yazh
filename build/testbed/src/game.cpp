#include"game.hpp"

inline bool Game::initialize() {
	Yazh::Core::Logger::Debug("Game::initialize() called!");
	return true;
}
bool Game::update(f32 deltaTime) {
	return true;
}
bool Game::render(f32 deltaTime) {
	return true;
}
void Game::onResize(u32 width, u32 height) {
}