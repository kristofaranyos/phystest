/*
 * A physics engine that runs simulations defined by PhysicsModule s on PhysicsEntity objects
 *
 * @version 1.0.0
 */

#include "PhysicsEngine.hpp"

//entities
#include "entity/PhysicsEntity.hpp"

//modules
#include "module/MoveModule.hpp"

/**
 * Defeault constructor resizes the modules vector to 0 and reserves 10
 */
PhysicsEngine::PhysicsEngine(SDLGraphicsWrapper &gWrapper) : m_graphicsWrapper(gWrapper) {
	this->m_modules.resize(0);
	this->m_modules.reserve(10);
}

/**
 * Adds a PhysicsModule to run in the simulation
 *
 * @param mod A PhysicsModule instance
 */
void PhysicsEngine::addModule(PhysicsModule &mod) {
	this->m_modules.emplace_back(mod);
}

void PhysicsEngine::run() {
	bool quit = false;

	//auxiliary variables for position calculations
	unsigned startTime = SDL_GetTicks(), firstTime;
	int mouseState, clicked = -1, clickTimes[2],  mousePositions[2][2];
	float startSpeed[2];

	//colors
	SDL_Color whiteColor = {255, 255, 255, 255};
	SDL_Color blackColor = {0, 0, 0, 255};

	while (!quit) {
		firstTime = SDL_GetTicks();
		while (SDL_PollEvent(&this->m_event)) {
			if (this->m_event.type == SDL_QUIT) {
				quit = true;
			} else if (this->m_event.type == SDL_KEYDOWN && this->m_event.key.keysym.sym == SDLK_ESCAPE) {
				quit = true;
			} else if (this->m_event.type == SDL_MOUSEBUTTONDOWN && this->m_event.button.button == SDL_BUTTON_LEFT) {
				clicked = 0;
				clickTimes[0] = SDL_GetTicks();
				mouseState = SDL_GetMouseState(&mousePositions[0][0], &mousePositions[0][1]);
			} else if (this->m_event.type == SDL_MOUSEBUTTONUP && this->m_event.button.button == SDL_BUTTON_LEFT) {
				clicked = 1;
				clickTimes[1] = SDL_GetTicks();
				mouseState = SDL_GetMouseState(&mousePositions[1][0], &mousePositions[1][1]);
			} else if (this->m_event.type == SDL_MOUSEBUTTONUP && this->m_event.button.button == SDL_BUTTON_RIGHT) {
				if (!this->m_entities.empty()) {
					std::cout << "removed entity: " << this->m_entities.size() - 1 << " at " << (SDL_GetTicks() - startTime) * TO_SEC << std::endl;
					this->m_entities.pop_back();
				}
			}

			if (clicked > 0) { //first click->0, second->1
				startSpeed[0] = (mousePositions[1][0] - mousePositions[0][0]) / ((clickTimes[1] - clickTimes[0]) * TO_SEC) * THROW_SPEEDX;
				startSpeed[1] = (mousePositions[1][1] - mousePositions[0][1]) / ((clickTimes[1] - clickTimes[0]) * TO_SEC) * THROW_SPEEDY;

				PhysicsEntity newEntity(this->m_entities.size(), mousePositions[1][0] - 10, mousePositions[1][1] - 10, 20, 20, startSpeed[0], startSpeed[1], 0.01f , SDL_GetTicks());
				this->m_entities.push_back(newEntity);

				std::cout << "added entity: " << newEntity.getEntityId() << " at " << (SDL_GetTicks() - startTime) * TO_SEC << std::endl;
				clicked = -1; //reset the flag
			}
		}

		//reset screen
		this->m_graphicsWrapper.drawColor(whiteColor);
		this->m_graphicsWrapper.renderClear();

		MoveModule move;

		//recalculate states
		for (auto &entity : this->m_entities) {
			move.runFrame(entity);

			//draw entity
			entity.draw(this->m_graphicsWrapper.getRenderer(), blackColor);
		}

		//draw changes
		this->m_graphicsWrapper.drawScreen();

		//if this int is an Uint32 it crashes for some reason
		int delay = FRAME_INTERVAL - (SDL_GetTicks() - firstTime);
		if (delay >= 0) {
			SDL_Delay((Uint32)delay);
		}
	}
}
