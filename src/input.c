#include "../include/input.h"

const Uint8 *keys;

bool inputCheckKey(SDL_Scancode key)
{
  // an sdl event is mandatory because the SDL_GetKeyboardState function only returns after processing all events
  SDL_Event ev;
  keys = SDL_GetKeyboardState(NULL);
  
  while(SDL_PollEvent(&ev))
  {
    if(keys[key])
    {
      return true;
    }
    break;
  }
  return false;
}

