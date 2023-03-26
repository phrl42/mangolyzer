#pragma once

#include "utils/incs.h"

#include "framework/Framework.h"
#include "renderer/RenderCommand.h"

#include <SDL2/SDL.h>

namespace banana
{
  class SDLFramework : public Framework
  {
  public:
    SDLFramework();
    ~SDLFramework() override;
    void Init(Uint32 flags) override;

    void SetColor(glm::vec4 color) override;
    void Clear() override;

    void Update(void* window) override;

  private:
    std::shared_ptr<RenderCommand> renderCommand;
  };
};