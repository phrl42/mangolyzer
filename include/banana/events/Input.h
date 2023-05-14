#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>

namespace banana
{
  class Input
  {
  public:
    static SDL_Event ev;
    static bool IsKeyDown(SDL_Scancode scancode);

    static void Check();
  };
};