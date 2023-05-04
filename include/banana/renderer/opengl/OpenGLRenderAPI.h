#pragma once
#include "renderer/RenderAPI.h"

namespace banana
{

  class OpenGLRenderAPI : public RenderAPI
  {
  public:
    static std::shared_ptr<OpenGLRenderAPI> GetOpenGLRenderAPI();
    ~OpenGLRenderAPI() override;

    void Init() override;
    OpenGLRenderAPI();
  };

};