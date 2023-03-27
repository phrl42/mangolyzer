#include "banana/window/SDLWindow.h"
#include <SDL2/SDL_video.h>

namespace banana
{
  SDLWindow::SDLWindow()
  {

  }

  SDLWindow::~SDLWindow()
  {
    SDL_GL_DeleteContext(con);
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

    // create context (only for opengl)
    switch(Management::UsedGL)
    {
      case GraphicsLibrary::OpenGL:
        con = SDL_GL_CreateContext(win);
        if(!con)
        {
          LOG_CORE("Could not create OpenGL Context");
        }
        
        if(SDL_GL_MakeCurrent(win, con) < 0)
        {
          LOG_CORE("Failed to make the OpenGL context active");
        }

        // enable v-sync
        if (SDL_GL_SetSwapInterval(1) == -1) 
        {
          LOG_CORE("Failed to enable v-sync: ");
        }
      break;
      case GraphicsLibrary::Vulkan:
        break;
    }
    
  }

  void* SDLWindow::GetWindow()
  {
    return win;
  }
}