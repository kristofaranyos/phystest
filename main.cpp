/*
 * main
 *
 * @version 1.0.0
 */

#include <iostream>
#include <vector>
#include <cmath>

#include <SDL2/SDL.h>

#include "SDLGraphicsWrapper.hpp"
#include "Constants.hpp"

#include "PhysicsEngine.hpp"

int main() {
	//disable c stream syncing
	std::ios::sync_with_stdio(false);

	SDLGraphicsWrapper wrapper(std::string("phystest"), 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TYPE);

	try {
		wrapper.init();
	} catch (const std::exception &e) {
		std::cout << e.what() << "\n";
		return 1;
	}


	PhysicsEngine engine(wrapper);
	engine.run();


	//quit close sdl
	SDL_DestroyRenderer(wrapper.getRenderer());
	SDL_DestroyWindow(wrapper.getWindow());
	SDL_Quit();

	return 0;
}