#pragma once

#include "utils/incs.h"
#include "game/info.h"

namespace banana
{
struct RenderStruct;

class Renderer
{
public:
  static void Init();
  static void Render();

  static void AddEntity();
  
  static RenderStruct renderInfo;
};

};