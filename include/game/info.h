#pragma once

#include "utils/incs.h"
#include "window/Window.h"
#include "utils/Management.h"

#include "game/Entity.h"

namespace game {

  struct BananaWindow 
  {
    int w;
    int h;
    glm::vec4 color;
    std::string title;
    std::shared_ptr<banana::Window> win;
  };

  class Banana
  {
  public:
    static int InitBananaWindow(BananaWindow& BWindow);
    static void AddRectangle(BananaRectangle& obj);
  };

}; // namespace banana
