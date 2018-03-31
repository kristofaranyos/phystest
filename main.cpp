/*
 * main
 *
 * @version 1.0.0
 */

#include <iostream>
#include <vector>
#include <cmath>

#include <SDL2/SDL.h>

#include "SDLWrapper.hpp"
#include "Constants.hpp"
#include "AABB.hpp"

int main() {
	//disable c stream syncing
	std::ios::sync_with_stdio(false);

	SDLWrapper wrapper(std::string("phystest"), 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TYPE);

	try {
		wrapper.init();
	} catch (const std::exception &e) {
		std::cout << e.what() << "\n";
		return 1;
	}

	//auxiliary variables for position calculations
	unsigned startTime = SDL_GetTicks(), firstTime;
	int mouseState, clicked = -1, clickTimes[2],  mousePositions[2][2];
	int tPosX, tPosY;
	float tSpeedY, tTime, startSpeed[2];

	//colors
	SDL_Color whiteColor = {255, 255, 255, 255};
	SDL_Color blackColor = {0, 0, 0, 255};

	//entity storage
	std::vector<AABB> entities;

	//main loop stuff
	SDL_Event e;
	bool quit = false;

	while (!quit) {
		firstTime = SDL_GetTicks();
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				quit = true;
			} else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
				quit = true;
			} else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
				clicked = 0;
				clickTimes[0] = SDL_GetTicks();
				mouseState = SDL_GetMouseState(&mousePositions[0][0], &mousePositions[0][1]);
			} else if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) {
				clicked = 1;
				clickTimes[1] = SDL_GetTicks();
				mouseState = SDL_GetMouseState(&mousePositions[1][0], &mousePositions[1][1]);
			} else if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_RIGHT) {
				if (!entities.empty()) {
					std::cout << "removed entity: " << entities.size() - 1 << " at " << (SDL_GetTicks() - startTime) * TO_SEC << std::endl;
					entities.pop_back();
				}
			}

			if (clicked > 0) { //first click->0, second->1
				startSpeed[0] = (mousePositions[1][0] - mousePositions[0][0]) / ((clickTimes[1] - clickTimes[0]) * TO_SEC) * THROW_SPEEDX;
				startSpeed[1] = (mousePositions[1][1] - mousePositions[0][1]) / ((clickTimes[1] - clickTimes[0]) * TO_SEC) * THROW_SPEEDY;

				AABB newEntity(entities.size(), mousePositions[1][0] - 10, mousePositions[1][1] - 10, 20, 20, startSpeed[0], startSpeed[1], 0.01f , SDL_GetTicks());
				entities.push_back(newEntity);

				std::cout << "added entity: " << newEntity.getEntityId() << " at " << (SDL_GetTicks() - startTime) * TO_SEC << std::endl;
				clicked = -1; //reset the flag
			}
		}

		//reset screen
		wrapper.drawColor(whiteColor);
		wrapper.renderClear();

		//recalculate states
		for (auto &entity : entities) {
			tTime = (SDL_GetTicks() - entity.getCreatedAt()) * TO_SEC;
			tSpeedY = entity.getVel().second + GRAVITY * tTime;
			tPosX = (int)std::round(entity.getPos().first + entity.getVel().first * tTime);
			tPosY = (int)std::round(entity.getPos().second + entity.getVel().second * tTime + GRAVITY / 2.f * tTime * tTime);

			//X bounds
			if (tPosX < 0) {
				entity.setPos(std::pair<int, int>(0, 0), AABB::ParamSelect::First);
				entity.setVel(std::pair<float, float>(-entity.getVel().first * WALL_BOUNCE, 0.f), AABB::ParamSelect::First);
			} else if (tPosX > SCREEN_WIDTH - entity.getSize().first) {
				entity.setPos(std::pair<int, int>(SCREEN_WIDTH - entity.getSize().first, 0), AABB::ParamSelect::First);
				entity.setVel(std::pair<float, float>(-entity.getVel().first * WALL_BOUNCE, 0.f), AABB::ParamSelect::First);
			} else {
				entity.setPos(std::pair<int, int>(tPosX, 0), AABB::ParamSelect::First);
			}


			//Y bounds
			if (tPosY < SCREEN_HEIGHT - entity.getSize().first) {
				entity.setPos(std::pair<int, int>(0, tPosY), AABB::ParamSelect::Second);
				entity.setVel(std::pair<float, float>(0.f, tSpeedY), AABB::ParamSelect::Second);
			} else {
				entity.setPos(std::pair<int, int>(0, SCREEN_HEIGHT - entity.getSize().second), AABB::ParamSelect::Second);
				entity.setVel(std::pair<float, float>(0.f, 0.f), AABB::ParamSelect::Second);
			}

			//friction
			if (tPosY >= SCREEN_HEIGHT - entity.getSize().first) {
				if (entity.getVel().first > 0) {
					if (entity.getVel().first - GRAVITY * entity.getFricCoeff() * tTime > 0) {
						float newVelX = entity.getVel().first - GRAVITY * entity.getFricCoeff() * tTime;
						entity.setVel(std::pair<int, int>(newVelX, 0), AABB::ParamSelect::First);

						int newX = entity.getPos().first - (int)std::round((GRAVITY * entity.getFricCoeff() * tTime) / 2 * tTime * tTime);
						entity.setPos(std::pair<int, int>(newX, 0), AABB::ParamSelect::First);
					} else {
						entity.setVel(std::pair<float, float>(0.f, 0.f), AABB::ParamSelect::First);
					}
				} else if (entity.getVel().first < 0) {
					if (entity.getVel().first + GRAVITY * entity.getFricCoeff() * tTime < 0) {
						float newVelX = entity.getVel().first + GRAVITY * entity.getFricCoeff() * tTime;
						entity.setVel(std::pair<int, int>(newVelX, 0), AABB::ParamSelect::First);

						int newX = entity.getPos().first + (int)std::round((GRAVITY * entity.getFricCoeff() * tTime) / 2 * tTime * tTime);
						entity.setPos(std::pair<int, int>(newX, 0), AABB::ParamSelect::First);
					} else {
						entity.setVel(std::pair<float, float>(0.f, 0.f), AABB::ParamSelect::First);
					}
				}
			}

			//draw entity
			entity.draw(wrapper.getRenderer(), blackColor);
		}

		//draw changes
		wrapper.drawScreen();

		//if this int is an Uint32 it crashes for some reason
		int delay = FRAME_INTERVAL - (SDL_GetTicks() - firstTime);
		if (delay >= 0) {
			SDL_Delay((Uint32)delay);
		}
	}

	//quit close sdl
	SDL_DestroyRenderer(wrapper.getRenderer());
	SDL_DestroyWindow(wrapper.getWindow());
	SDL_Quit();

	return 0;
}