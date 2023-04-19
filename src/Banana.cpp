#include "game/info.h"

namespace banana
{
    int Banana::InitBananaWindow(BananaWindow* BWindow) 
    {
      // use 0 for an OpenGL Context (recommended)
      // the standard sdl renderer is not supported anymore..
      /* flags:
      --------------------------------------------------------------------------------
      SDL_WINDOW_FULLSCREEN: fullscreen window
      SDL_WINDOW_FULLSCREEN_DESKTOP: fullscreen window at desktop resolution
      SDL_WINDOW_OPENGL: window usable with an OpenGL context
      SDL_WINDOW_VULKAN: window usable with a Vulkan instance
      SDL_WINDOW_METAL: window usable with a Metal instance
      SDL_WINDOW_HIDDEN: window is not visible
      SDL_WINDOW_BORDERLESS: no window decoration
      SDL_WINDOW_RESIZABLE: window can be resized
      SDL_WINDOW_MINIMIZED: window is minimized
      SDL_WINDOW_MAXIMIZED: window is maximized
      SDL_WINDOW_INPUT_GRABBED: window has grabbed input focus
      SDL_WINDOW_ALLOW_HIGHDPI: window should be created in high-DPI mode if
      supported
      --------------------------------------------------------------------------------
      */
      BWindow->win = Window::GetWindowWS();
      BWindow->win->BackgroundColor = BWindow->color;
      BWindow->win->Init(BWindow->title, BWindow->w, BWindow->h);

      // save window
      Window::Windows.push_back(BWindow->win);
      return 0;
    };
    
    int Banana::AddRectangle(BananaRectangle& obj)
    {
      Renderer::AddRectangle(obj->x, obj->y, obj->w, obj->h, obj->r, obj->g, obj->b, -1, obj->proj);
    }
};