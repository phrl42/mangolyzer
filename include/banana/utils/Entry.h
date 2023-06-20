#pragma once

#include "incs.h"

#include "framework/Framework.h"

#include "renderer/RenderAPI.h"
#include "renderer/RenderCommand.h"

#include "game/Game.h"

namespace banana 
{
  
  class Entry 
  {
  public:
    Entry();
    ~Entry();
    
    void Run();

    void Init();

  private:
    std::shared_ptr<Framework> framework;
    std::shared_ptr<RenderCommand> renderCommand;
    std::shared_ptr<RenderAPI> renderAPI;

    std::shared_ptr<game::Game> GameScene;
  };

} // namespace banana
