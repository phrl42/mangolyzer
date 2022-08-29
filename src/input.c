#include "input.h"

SDL_KeyCode inputHandleKeyboard()
{
  SDL_Event ev;

  while(SDL_PollEvent(&ev))
  {
    switch(ev.type)
    {
      case SDL_KEYDOWN:
        
        switch(ev.key.keysym.sym)
        {
          default:
            return ev.key.keysym.sym;
            break;
        }
        
        break;

      default:
        break;
    }
  }
  return 0;
}
