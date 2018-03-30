//
// Created by kristof on 2018.03.30..
//

#include "SDLWrapper.h"
#include <stdexcept>

SDLWrapper::SDLWrapper(std::string name, int posX, int posY, int width, int height, Uint32 type)
	: m_name(name)
	, m_posX(posX)
	, m_posY(posY)
	, m_screenWidth(width)
	, m_screenHeight(height)
	, m_windowType(type) {
}

void SDLWrapper::init() {
	if (SDL_InitSubSystem(SDL_INIT_EVERYTHING) != 0) {
		throw std::runtime_error(std::string("SDL_InitSubSystem error: ").append(SDL_GetError()));
	}

	this->m_window = SDL_CreateWindow(this->m_name.c_str(), this->m_posX, this->m_posY, this->m_screenWidth, this->m_screenHeight, this->m_windowType);
	if (this->m_window == nullptr) {
		SDL_Quit();
		throw std::runtime_error(std::string("CreateWindow error: ").append(SDL_GetError()));
	}

	this->m_renderer = SDL_CreateRenderer(this->m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (this->m_renderer == nullptr) {
		SDL_DestroyWindow(this->m_window);
		SDL_Quit();
		throw std::runtime_error(std::string("CreateRenderer error: ").append(SDL_GetError()));
	}
}

void SDLWrapper::drawColor(SDL_Color color) {
	SDL_SetRenderDrawColor(this->m_renderer, color.r, color.g, color.b, color.a);
}

void SDLWrapper::renderClear() {
	SDL_RenderClear(this->m_renderer);
}

void SDLWrapper::drawScreen() {
	SDL_RenderPresent(this->m_renderer);
}

SDL_Window *SDLWrapper::getWindow() {
	return this->m_window;
}

SDL_Renderer *SDLWrapper::getRenderer() {
	return this->m_renderer;
}
