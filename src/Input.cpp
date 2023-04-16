#include "events/Input.h"
#include "utils/Log.h"

#include <SDL2/SDL.h>

namespace banana
{
  bool Input::IsKeyDown(SDL_Scancode scancode)
  {
    SDL_Event ev;
    const Uint8 *keys = SDL_GetKeyboardState(NULL);

    while(SDL_PollEvent(&ev))
    {
      if(keys[scancode])
      {
        return true;
      }
    }
    
    return false;
  }

}