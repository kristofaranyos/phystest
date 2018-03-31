/*
 * A physics engine that runs simulations defined by PhysicsModule s on PhysicsEntity objects
 *
 * @version 1.0.0
 */

#include "PhysicsEngine.hpp"

/**
 * Defeault constructor resizes the modules vector to 0 and reserves 10
 */
PhysicsEngine::PhysicsEngine(SDLGraphicsWrapper &wrapper) : m_wrapper(wrapper) {
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
	int tPosX, tPosY;
	float tSpeedY, tTime, startSpeed[2];

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
		this->m_wrapper.drawColor(whiteColor);
		this->m_wrapper.renderClear();

		//recalculate states
		for (auto &entity : this->m_entities) {
			tTime = (SDL_GetTicks() - entity.getCreatedAt()) * TO_SEC;
			tSpeedY = entity.getVel().second + GRAVITY * tTime;
			tPosX = (int)std::round(entity.getPos().first + entity.getVel().first * tTime);
			tPosY = (int)std::round(entity.getPos().second + entity.getVel().second * tTime + GRAVITY / 2.f * tTime * tTime);

			//X bounds
			if (tPosX < 0) {
				entity.setPos(std::pair<int, int>(0, 0), PhysicsEntity::ParamSelect::First);
				entity.setVel(std::pair<float, float>(-entity.getVel().first * WALL_BOUNCE, 0.f), PhysicsEntity::ParamSelect::First);
			} else if (tPosX > SCREEN_WIDTH - entity.getSize().first) {
				entity.setPos(std::pair<int, int>(SCREEN_WIDTH - entity.getSize().first, 0), PhysicsEntity::ParamSelect::First);
				entity.setVel(std::pair<float, float>(-entity.getVel().first * WALL_BOUNCE, 0.f), PhysicsEntity::ParamSelect::First);
			} else {
				entity.setPos(std::pair<int, int>(tPosX, 0), PhysicsEntity::ParamSelect::First);
			}

			//Y bounds
			if (tPosY < SCREEN_HEIGHT - entity.getSize().first) {
				entity.setPos(std::pair<int, int>(0, tPosY), PhysicsEntity::ParamSelect::Second);
				entity.setVel(std::pair<float, float>(0.f, tSpeedY), PhysicsEntity::ParamSelect::Second);
			} else {
				entity.setPos(std::pair<int, int>(0, SCREEN_HEIGHT - entity.getSize().second), PhysicsEntity::ParamSelect::Second);
				entity.setVel(std::pair<float, float>(0.f, 0.f), PhysicsEntity::ParamSelect::Second);
			}

			//friction
			if (tPosY >= SCREEN_HEIGHT - entity.getSize().first) {
				if (entity.getVel().first > 0) {
					if (entity.getVel().first - GRAVITY * entity.getFricCoeff() * tTime > 0) {
						float newVelX = entity.getVel().first - GRAVITY * entity.getFricCoeff() * tTime;
						entity.setVel(std::pair<int, int>(newVelX, 0), PhysicsEntity::ParamSelect::First);

						int newX = entity.getPos().first - (int)std::round((GRAVITY * entity.getFricCoeff() * tTime) / 2 * tTime * tTime);
						entity.setPos(std::pair<int, int>(newX, 0), PhysicsEntity::ParamSelect::First);
					} else {
						entity.setVel(std::pair<float, float>(0.f, 0.f), PhysicsEntity::ParamSelect::First);
					}
				} else if (entity.getVel().first < 0) {
					if (entity.getVel().first + GRAVITY * entity.getFricCoeff() * tTime < 0) {
						float newVelX = entity.getVel().first + GRAVITY * entity.getFricCoeff() * tTime;
						entity.setVel(std::pair<int, int>(newVelX, 0), PhysicsEntity::ParamSelect::First);

						int newX = entity.getPos().first + (int)std::round((GRAVITY * entity.getFricCoeff() * tTime) / 2 * tTime * tTime);
						entity.setPos(std::pair<int, int>(newX, 0), PhysicsEntity::ParamSelect::First);
					} else {
						entity.setVel(std::pair<float, float>(0.f, 0.f), PhysicsEntity::ParamSelect::First);
					}
				}
			}

			//draw entity
			entity.draw(this->m_wrapper.getRenderer(), blackColor);
		}

		//draw changes
		this->m_wrapper.drawScreen();

		//if this int is an Uint32 it crashes for some reason
		int delay = FRAME_INTERVAL - (SDL_GetTicks() - firstTime);
		if (delay >= 0) {
			SDL_Delay((Uint32)delay);
		}
	}
}
