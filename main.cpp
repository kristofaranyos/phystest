/**
 * main
 *
 * @author kristof
 * @version 1.0.0
 */

#include <iostream>
#include <vector>
#include <cmath>

#include <SDL2/SDL.h>

#include "SDLWrapper.h"
#include "Constants.h"
#include "AABB.h"

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
	float tSpeedX, tSpeedY, tTime, startSpeed[2];

	std::vector<AABB> entities;
	SDL_Event e;
	bool quit = false;

	SDL_Color color = {0, 0, 0, 255};

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

				AABB newEntity(entities.size(), mousePositions[1][0] - 10, mousePositions[1][1] - 10, 20, 20, startSpeed[0], startSpeed[1], SDL_GetTicks());
				entities.push_back(newEntity);

				std::cout << "added entity: " << newEntity.getEntityId() << " at " << (SDL_GetTicks() - startTime) * TO_SEC << std::endl;
				clicked = -1; //reset the flag
			}
		}

		//reset screen
		SDL_SetRenderDrawColor(wrapper.getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(wrapper.getRenderer());


		//recalculate states
		for (auto &entity : entities) {
			tTime = (SDL_GetTicks() - entity.getCreatedAt()) * TO_SEC;
			tSpeedY = entity.getVel().second + GRAVITY * tTime; //todo do something with this
			tPosX = (int)std::round(entity.getPos().first + entity.getVel().first * tTime);
			tPosY = (int)std::round(entity.getPos().second + entity.getVel().second * tTime + GRAVITY / 2.f * tTime * tTime); //todo do something with this

			//X bounds
			//todo unfuck x bounds
			if (tPosX < 0) {
				entity.setPos(std::pair<int, int>(0, 0), AABB::ParamSelect::First);
				entity.setVel(std::pair<float, float>(-entity.getVel().first * WALL_BOUNCE, 0.f), AABB::ParamSelect::First);
			} else if (tPosX > SCREEN_WIDTH - entity.getSize().first) {
				entity.setPos(std::pair<int, int>(SCREEN_WIDTH - entity.getSize().first, 0), AABB::ParamSelect::First);
				entity.setVel(std::pair<float, float>(-entity.getVel().first * WALL_BOUNCE, 0.f), AABB::ParamSelect::First);
			} else {
				entity.setPos(std::pair<int, int>(tPosX, 0), AABB::ParamSelect::First);
			}

			//todo implement y bounds
			/*
			//Y bounds
			if (tPosY < SCREEN_HEIGHT - entities[i].r) {
				entities[i].y = tPosY;
				entities[i].velY = tSpeedY;
			} else {
				entities[i].y = SCREEN_HEIGHT - entities[i].r;
				entities[i].velY = 0;
				if (entities[i].velX > 0) {
					if (entities[i].velX - GRAVITY * entities[i].fricCoeff * tTime > 0) {
						entities[i].velX -= GRAVITY * entities[i].fricCoeff * tTime;
						entities[i].x -= (GRAVITY * entities[i].fricCoeff * tTime) / 2 * tTime * tTime;
					} else {
						entities[i].velX = 0;
					}
				} else if (entities[i].velX < 0) {
					if (entities[i].velX + GRAVITY * entities[i].fricCoeff * tTime < 0) {
						entities[i].velX += GRAVITY * entities[i].fricCoeff * tTime;
						entities[i].x += (GRAVITY * entities[i].fricCoeff * tTime) / 2 * tTime * tTime;
					} else {
						entities[i].velX = 0;
					}
				}
			}
			*/

			//draw entity
			entity.draw(wrapper.getRenderer(), color);

		}

		//draw show changes
		SDL_RenderPresent(wrapper.getRenderer());

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