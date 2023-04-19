#pragma once

#include "utils/incs.h"
#include "window/Window.h"
#include "utils/Management.h"

namespace banana {

enum class Projection { NONE = 0, ORTHOGRAPHIC, PERSPECTIVE };

struct BananaWindow 
{
public:
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

    enum Projection proj;
  };

  struct BananaTexture 
  {
    float x;
    float y;

    int w;
    int h;

    enum Projection proj;

    const char *path;
    unsigned char *data;

    int channels;
    unsigned int textureID;
  };
class Banana {

public:
  static int InitBananaWindow(BananaWindow* BWindow);

  static int AddRectangle(BananaRectangle& obj);

};

}; // namespace banana