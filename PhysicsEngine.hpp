/*
 * PhysicsEngine declarations
 *
 * @version 1.0.0
 */

#ifndef PHYSTEST_PHYSICSENGINE_HPP
#define PHYSTEST_PHYSICSENGINE_HPP


#include "PhysicsIncludes.hpp"
#include "SDLGraphicsWrapper.hpp"

class PhysicsEngine {
private:
	SDL_Event m_event;
	SDLGraphicsWrapper m_graphicsWrapper;
	std::vector<PhysicsModule> m_modules;
	std::vector<PhysicsEntity> m_entities;
public:
	PhysicsEngine(SDLGraphicsWrapper &wrapper);

	void addModule(PhysicsModule &mod);
	void run();
};


#endif //PHYSTEST_PHYSICSENGINE_HPP
