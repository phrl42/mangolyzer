#include "window/Context.h"

#include <SDL2/SDL.h>

#include "utils/glad.h"

namespace banana
{
  class OpenGLContext : public Context
  {
  public:
    OpenGLContext();
    ~OpenGLContext() override;

    void SetContext(void* win) override;
    void* GetContext() override;

  private:
    SDL_GLContext con;
  };
};