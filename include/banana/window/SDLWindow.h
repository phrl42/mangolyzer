#pragma once

#include "utils/incs.h"
#include "game/info.h"

#include "window/Window.h"
#include "window/Context.h"

#include <SDL2/SDL.h>

namespace banana
{
  class SDLWindow : public Window
  {
  public:
    SDLWindow();
    ~SDLWindow() override;

    void Init(std::string title, int width, int height) override;

    void* GetWindow() override;

    void SetUseInfo();
  private:
    SDL_Window* win;
    std::shared_ptr<Context> con;
  };
};
