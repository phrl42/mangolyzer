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

    Uint64 GetTicks() override;

    void SetWindowTitle(void* window, std::string title) override;

    void Clear() override;

    void Update(void* window) override;

    std::shared_ptr<RenderCommand> renderCommand;
  };
};