#pragma once
#include "utils/incs.h"

#include "game/info.h"

namespace game
{
  class Game
  {
  public:
    static void Init();
    static void Loop(float dt);
  private:
    static banana::BananaWindow win;
    static banana::BananaRectangle rect;
    static banana::BananaRectangle rect2;

  };
};