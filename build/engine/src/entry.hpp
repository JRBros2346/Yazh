#pragma once

#include"defines.hpp"
#include"core/application.hpp"
#include"core/logger.hpp"
#include"core/ymemory.hpp"
#include"game_types.hpp"

//#include"types/vector.hpp"
//#include<iostream>

// Externally defined function to create game.
namespace Yazh { Yazh::VirtualGame* createGame(); }

/**
 * The main entry point of the app.
 */
int main(void) {
	
	Yazh::Memory::initialize();

//	Yazh::Types::Vector<u64> v(3);
//	v.push(5);
//	v.push(6);
//	v.push(7);
//	v.push(8);
//	v.push(9);
//	v.push(10);
//	v.push(11);
//	v.push(12);
//	v.push(13);
//	v.push(14);
//	v.push(15);
//	v.pop(2);
//	v.push(123,4);
//	v.pop();
//	v.push(105);
//	v.push(106);
//	v.push(107);
//	v.push(108);
//	v.push(109);
//	v.push(110);
//	std::cout << "[ "; for (u64 i = 0; i < v.size(); i++) std::cout << v[i] << ' '; std::cout << "]" << std::endl;
//	std::cout << "Size: " << v.size() << std::endl;
//	std::cout << "Capacity: " << v.capacity() << std::endl;
	
	// Request the game instance from the app.
	Yazh::VirtualGame* game = Yazh::createGame();
	if (!game) {
		YFATAL("Could not create game!");
		return -1;
	}
	
	// Initialization
	if (!Yazh::Application::create(game)) {
		YINFO("Application failed to create!");
		return 1;
	}
	
	// Begin the game loop.
	if (!Yazh::Application::run()) {
		YINFO("Application did not shutdown gracefully");
		return 2;
	}
	
	Yazh::Memory::shutdown();
	
	return 0;
}
