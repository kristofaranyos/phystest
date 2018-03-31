/*
 * PhysicsEngine declarations
 *
 * @version 1.0.0
 */

#ifndef PHYSTEST_PHYSICSENGINE_HPP
#define PHYSTEST_PHYSICSENGINE_HPP


#include <iostream>
#include <vector>
#include <cmath>

#include <SDL2/SDL.h>

#include "Constants.hpp"

#include "module/PhysicsModule.hpp"
#include "entity/PhysicsEntity.hpp"
#include "SDLGraphicsWrapper.hpp"

class PhysicsEngine {
private:
	SDL_Event m_event;
	SDLGraphicsWrapper m_wrapper;
	std::vector<PhysicsModule> m_modules;
	std::vector<PhysicsEntity> m_entities;
public:
	PhysicsEngine(SDLGraphicsWrapper &wrapper);

	void addModule(PhysicsModule &mod);
	void run();
};


#endif //PHYSTEST_PHYSICSENGINE_HPP
