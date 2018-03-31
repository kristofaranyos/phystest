/*
 * Basic SDL2 wrapper for easier usage
 *
 * @version 1.0.0
 */

#include "SDLWrapper.hpp"
#include <stdexcept>

/**
 * Constructor for passing window application properties
 *
 * @author kristof
 *
 * @param name Application name that appears in the title bar
 * @param posX x position of the top left corner of the window
 * @param posY y position of the top left corner of the window
 * @param width Width of the window
 * @param height Height of the window
 * @param type Init flags as described in SDL2 documentation of SDL_InitSubSystem
 */
SDLWrapper::SDLWrapper(std::string name, int posX, int posY, int width, int height, Uint32 flags)
	: m_name(name)
	, m_posX(posX)
	, m_posY(posY)
	, m_screenWidth(width)
	, m_screenHeight(height)
	, m_windowFlags(flags) {
}

/**
 * Initializes the SDL system itself
 *
 * @author kristof
 *
 * @throws std::runtime_error When an error occurs in SDL init process
 */
void SDLWrapper::init() {
	if (SDL_InitSubSystem(SDL_INIT_EVERYTHING) != 0) {
		throw std::runtime_error(std::string("SDL_InitSubSystem error: ").append(SDL_GetError()));
	}

	this->m_window = SDL_CreateWindow(this->m_name.c_str(), this->m_posX, this->m_posY, this->m_screenWidth, this->m_screenHeight, this->m_windowFlags);
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

/**
 * Sets the drawcolor
 *
 * @author kristof
 *
 * @param color Color to use for drawing
 */
void SDLWrapper::drawColor(SDL_Color color) {
	SDL_SetRenderDrawColor(this->m_renderer, color.r, color.g, color.b, color.a);
}

/**
 * Clears the screen
 *
 * @author kristof
 */
void SDLWrapper::renderClear() {
	SDL_RenderClear(this->m_renderer);
}

/**
 * Draws changes made to the screen
 *
 * @author kristof
 */
void SDLWrapper::drawScreen() {
	SDL_RenderPresent(this->m_renderer);
}

/**
 * Returns the pointer to the current window
 *
 * @author kristof
 *
 * @return m_window
 */
SDL_Window *SDLWrapper::getWindow() {
	return this->m_window;
}

/**
 * Returns the pointer to the current renderer
 *
 * @author kristof
 *
 * @return m_renderer
 */
SDL_Renderer *SDLWrapper::getRenderer() {
	return this->m_renderer;
}
