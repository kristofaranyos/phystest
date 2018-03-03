#include <iostream>
#include <vector>

#include <SDL2/SDL.h>

#include "Constants.h"


//axis aligned bounding boxes for rectangles
typedef struct {
	unsigned long id;
	int x;
	int y;
	int w;
	int h;
	float velX; // positive = right, negative = left
	float velY; // positive = down. negative = up
	unsigned timestamp;
} AABB;

typedef struct {
	unsigned long id;
	int x;
	int y;
	int r;
	float velX; // positive = right, negative = left
	float velY; // positive = down. negative = up
	float ang;
	float velAng;
	float fricCoeff;
	unsigned timestamp;
	unsigned yMaxTime;
} Circle;

void drawCircle(SDL_Renderer *renderer, Circle circle, SDL_Color color) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	for (int i = 1 - circle.r; i < circle.r ; ++i) {
		for (int j = 1 - circle.r; j < circle.r; ++j) {
			if ((i*i + j*j) <= (circle.r * circle.r)) {
				SDL_RenderDrawPoint(renderer, circle.x + i, circle.y + j);
			}
		}
	}
}

int main() {
    //disable c stream syncing
	std::ios::sync_with_stdio(false);

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "SDL_Init error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Window *window = SDL_CreateWindow("physics simulator", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TYPE);
	if (window == nullptr) {
		std::cout << "CreateWindow error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		std::cout << "CreateRenderer error: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	//auxiliary variables for position calculations
	unsigned startTime = SDL_GetTicks(), firstTime;
	int mouseState, clicked = -1, clickTimes[2],  mousePositions[2][2];
	int tPosX, tPosY;
	float tSpeedX, tSpeedY, tTime, startSpeed[2];

	std::vector<Circle> entities;
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
				if (entities.size() > 0) {
					std::cout << "removed entity: " << entities.size() - 1 << " at " << (SDL_GetTicks() - startTime) * TO_SEC << std::endl;
					entities.pop_back();
				}
			}

			if (clicked > 0) { //first click->0, second->1
				startSpeed[0] = (mousePositions[1][0] - mousePositions[0][0]) / ((clickTimes[1] - clickTimes[0]) * TO_SEC) * THROW_SPEEDX;
				startSpeed[1] = (mousePositions[1][1] - mousePositions[0][1]) / ((clickTimes[1] - clickTimes[0]) * TO_SEC) * THROW_SPEEDY;

				Circle newEntity = {entities.size(), mousePositions[1][0], mousePositions[1][1], 20, startSpeed[0], startSpeed[1], 0, 0, 1, SDL_GetTicks(), 0};
				entities.push_back(newEntity);

				std::cout << "added entity: " << newEntity.id << " at " << (SDL_GetTicks() - startTime) * TO_SEC << std::endl;
				clicked = -1; //reset the flag
			}
		}

		//reset screen
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);

		//recalculate states
		for (int i = 0; i < entities.size(); ++i) {
			tTime = (SDL_GetTicks() - entities[i].timestamp) * TO_SEC;
			tSpeedY = entities[i].velY + GRAVITY * tTime;
            //these should be floats
			tPosX = entities[i].x + entities[i].velX * tTime;
			tPosY = entities[i].y + entities[i].velY * tTime + GRAVITY / 2.f * tTime * tTime;

			//X bounds
			if (tPosX < entities[i].r) {
				entities[i].x = entities[i].r;
				entities[i].velX = -entities[i].velX * WALL_BOUNCE;
			} else if (tPosX > SCREEN_WIDTH - entities[i].r) {
				entities[i].x = SCREEN_WIDTH - entities[i].r;
				entities[i].velX = -entities[i].velX * WALL_BOUNCE;
			} else {
				entities[i].x = tPosX;
			}

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
		}

		//draw objects
		for (int i = 0; i < entities.size(); ++i) {
			SDL_Color color = {0, 0, 0, 255};
			drawCircle(renderer, entities[i], color);
		}

		SDL_RenderPresent(renderer);
		int delay = FRAME_INTERVAL - (SDL_GetTicks() - firstTime);
		if (delay >= 0) {
			SDL_Delay(delay);
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}