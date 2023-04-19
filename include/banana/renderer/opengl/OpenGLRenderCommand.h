#pragma once 

#include "utils/incs.h"
#include "renderer/RenderCommand.h"

namespace banana
{
  class OpenGLRenderCommand : public RenderCommand
  {
  public:
    OpenGLRenderCommand();
    ~OpenGLRenderCommand() override;

    void Clear() override;
    void InitRenderer() override;
    void SetColor(glm::vec4 color) override;
    void Update(void* window) override;
  };
};
