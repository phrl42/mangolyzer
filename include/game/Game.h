#pragma once
#include "utils/incs.h"

#include "game/info.h"

namespace game
{
  class Game
  {
  public:
    void Init();
    void Loop(float dt);
  private:
    BananaWindow win;
    BananaRectangle rect;
    BananaRectangle rect2;
    BananaRectangle rect3;
  };
};