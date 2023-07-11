#pragma once

#include"defines.hpp"
#include"core/application.hpp"
#include"core/logger.hpp"
#include"core/ymemory.hpp"
#include"game_types.hpp"

// #include"types/vector.hpp"
// #include<iostream>

// Externally defined function to create game.
namespace Yazh::Game { VirtualGame* createGame(); }

/**
 * The main entry point of the app.
 */
int main(void) {
	
	Yazh::Memory::initialize();

	// Yazh::Types::Vector<u64> v(4);
	// v.push_back(5);
	// v.push_back(6);
	// v.push_back(7);
	// v.push_back(8);
	// v.push_back(9);
	// v.push_back(10);
	// v.push_back(11);
	// v.push_back(12);
	// v.push_back(13);
	// v.push_back(14);
	// v.push_back(15);
	// v.pop_at(2);
	// v.push_at(4, 123);
	// v.pop_back();
	// v.push_back(105);
	// v.push_back(106);
	// v.push_back(107);
	// v.push_back(108);
	// v.push_back(109);
	// v.push_back(110);
	// v.emplace_back(1024);
	// v.emplace_at(10, 999);
	// std::cout << "[ "; for (ysize i = 0; i < v.size(); ++i) std::cout << v[i] << ' '; std::cout << "]" << std::endl;
	// std::cout << "Size: " << v.size() << std::endl;
	// std::cout << "Capacity: " << v.capacity() << std::endl;
	
	// Request the game instance from the app.
	Yazh::Game::VirtualGame* game = Yazh::Game::createGame();
	if (!game) {
		Yazh::Logger::Fatal("Could not create game!");
		return -1;
	}
	
	// Initialization
	if (!Yazh::Application::create(game)) {
		Yazh::Logger::Info("Application failed to create!");
		return 1;
	}
	
	// Begin the game loop.
	if (!Yazh::Application::run()) {
		Yazh::Logger::Info("Application did not shutdown gracefully");
		return 2;
	}
	
	Yazh::Memory::shutdown();
	
	return 0;
}
