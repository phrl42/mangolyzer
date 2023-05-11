#pragma once

#include "utils/incs.h"
#include "window/Window.h"
#include "utils/Management.h"

namespace banana {

  enum class Projection { NONE = 0, ORTHOGRAPHIC, PERSPECTIVE };

  struct BananaWindow 
  {
    int w;
    int h;
    glm::vec4 color;
    std::string title;
    std::shared_ptr<Window> win;
  };

  struct BananaRectangle 
  {
    float x;
    float y;

    float w;
    float h;

    float r;
    float g;
    float b;
    float a;

    //std::shared_ptr<Texture> tex;

    enum Projection proj;
  };

  class Banana
  {
  public:
    static int InitBananaWindow(BananaWindow& BWindow);
    static void AddRectangle(BananaRectangle& obj);

  };

}; // namespace banana
