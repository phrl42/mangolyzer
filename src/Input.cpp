#include "events/Input.h"
#include "utils/Log.h"

namespace banana
{
  SDL_Event Input::ev;
  bool Input::IsKeyDown(SDL_Scancode scancode)
  {
    Check();
    const Uint8 *keys = SDL_GetKeyboardState(NULL);

    //while(SDL_PollEvent(&ev))
    //{
      if(keys[scancode])
      {
        return true;
      }
    //}
    
    return false;
  }

  void Input::Check()
  {
    SDL_PollEvent(&ev);
  }

}