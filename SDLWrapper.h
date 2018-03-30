//
// Created by kristof on 2018.03.30..
//

#ifndef PHYSTEST_SDLWRAPPER_H
#define PHYSTEST_SDLWRAPPER_H

#include <iostream>
#include <SDL2/SDL.h>

class SDLWrapper {
private:
	std::string m_name;
	int m_posX, m_posY;
	const int m_screenWidth, m_screenHeight;
	const Uint32 m_windowType;

	SDL_Window *m_window;
	SDL_Renderer *m_renderer;
public:
	SDLWrapper(std::string name, int posX, int posY, int width, int height, Uint32 type);

	void init();
	void drawColor(SDL_Color color);
	void renderClear();
	void drawScreen();

	SDL_Window *getWindow();
	SDL_Renderer *getRenderer();
};


#endif //PHYSTEST_SDLWRAPPER_H