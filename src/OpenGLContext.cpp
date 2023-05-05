#include "window/OpenGLContext.h"

namespace banana
{
  OpenGLContext::OpenGLContext()
  {

  }

  OpenGLContext::~OpenGLContext()
  {
    SDL_GL_DeleteContext(con);
  }

  void OpenGLContext::SetContext(void* win)
  {
    // set opengl version and
    // disallow older gl functions
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
     
    con = SDL_GL_CreateContext((SDL_Window*)win);
    if(!con)
    {
      LOG_CORE("Could not create SDL_GLContext");
    }

    if(SDL_GL_MakeCurrent((SDL_Window*)win, con) < 0)
    {
      LOG_CORE("Failed to make the OpenGL context active");
    }

    // enable v-sync
    if (SDL_GL_SetSwapInterval(1) == -1) 
    {
      LOG_CORE("Failed to enable v-sync: ");
    }
  }

  void* OpenGLContext::GetContext()
  {
    return con;
  }
};