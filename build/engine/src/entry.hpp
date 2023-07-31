#pragma once

#include"defines.hpp"
#include"core/application.hpp"
#include"core/logger.hpp"
#include"core/ymemory.hpp"
#include"game_types.hpp"

#include"types/vector.hpp"

// Externally defined function to create game.
namespace Yazh::Game { extern VirtualGame* createGame(); }

/**
 * The main entry point of the app.
 */
int main(void) {
	Yazh::Types::Vector<bool> v;
	v.push_back(true);
	v.push_back(false);
	v.push_back(true);
	v.push_back(true);
	for (const auto& e : v)
		Yazh::Core::Logger::Debug("{}", e);
	
	
	Yazh::Core::Memory::initialize();
	
	// Request the game instance from the app.
	Yazh::Game::VirtualGame* game = Yazh::Game::createGame();
	if (!game) {
		Yazh::Core::Logger::Fatal("Could not create game!");
		return -1;
	}
	
	// Initialization
	if (!Yazh::Core::Application::create(game)) {
		Yazh::Core::Logger::Info("Application failed to create!");
		return 1;
	}
	
	// Begin the game loop.
	if (!Yazh::Core::Application::run()) {
		Yazh::Core::Logger::Info("Application did not shutdown gracefully");
		return 2;
	}
	
	Yazh::Core::Memory::shutdown();
	
	return 0;
}
