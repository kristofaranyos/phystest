/*
 * main
 *
 * @version 1.0.0
 */

#include <iostream>

#include <SDL2/SDL.h>

#include "Constants.hpp"

#include "SDLGraphicsWrapper.hpp"
#include "PhysicsEngine.hpp"

//modules
#include "module/MoveModule.hpp"

int main() {
	//disable c stream syncing
	std::ios::sync_with_stdio(false);

	SDLGraphicsWrapper gWrapper(std::string("phystest"), 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TYPE);

	try {
		gWrapper.init();
	} catch (const std::exception &e) {
		std::cout << e.what() << "\n";
		return 1;
	}

	PhysicsEngine engine(gWrapper);

	engine.addModule(new MoveModule());
	engine.run();

	gWrapper.quit();

	return 0;
}