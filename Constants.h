/**
 * Constants for the simulator
 *
 * @author kristof
 * @version 1.0.0
 */

#ifndef PHYSTEST_CONSTANTS_H
#define PHYSTEST_CONSTANTS_H


#include <SDL2/SDL.h>

//graphics settings
const int SCREEN_WIDTH  = 1920;
const int SCREEN_HEIGHT = 1080;
const Uint32 WINDOW_TYPE = SDL_WINDOW_SHOWN;
// interval is 1/fps
const int FRAME_INTERVAL = 20; //50fps

//physics settings
const float GRAVITY = 9.81f;
const float THROW_SPEEDX = 000.1f;
const float THROW_SPEEDY = 00000.1f;
const float WALL_BOUNCE = 0.2f;

//constant constants
const float TO_SEC = 0.001f;


#endif //PHYSTEST_CONSTANTS_H
