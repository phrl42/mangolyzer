#include "banana/window/SDLWindow.h"
#include <SDL2/SDL_video.h>

namespace banana
{
  SDLWindow::SDLWindow()
  {

  }

  SDLWindow::~SDLWindow()
  {
    SDL_DestroyWindow(win);
  }

  void SDLWindow::Init(std::string title, int width, int height)
  {
    Uint32 flags;

    switch(Management::UsedGL)
    {
      case GraphicsLibrary::OpenGL:
        flags = SDL_WINDOW_OPENGL;
        break;
      case GraphicsLibrary::Vulkan:
        flags = SDL_WINDOW_VULKAN;
        break;
    }

    win = SDL_CreateWindow(title.c_str(), 0, 0, width, height, flags);

    // create context
    con = Context::GetWindowContext();
    con->SetContext(win);
  }

  void* SDLWindow::GetWindow()
  {
    return win;
  }
}