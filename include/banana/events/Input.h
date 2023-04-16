#pragma once

#include <SDL2/SDL_keyboard.h>

namespace banana
{
  class Input
  {
  public:
    static bool IsKeyDown(SDL_Scancode scancode);
  };
};