#pragma once

#include "utils/incs.h"
#include "game/info.h"

namespace banana
{
class Renderer
{
public:
  static void Init();
  static void Render();

  static void AddRectangle(BananaRectangle& bRectangle);

};

};