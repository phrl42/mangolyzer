#pragma once
#include "_Banana.h"

#include "renderer/VertexArray.h"
#include "glm.hpp"

namespace Banana
{
  class RendererAPI 
  {
  public:
    enum class API
    {
      NONE = 0, OpenGL
    };

    virtual ~RendererAPI() = default;
    RendererAPI();

    virtual void Clear() = 0;
    virtual void SetClearColor(const glm::vec4& color) = 0;

    virtual void DrawIndexed(const Shr<VertexArray>& vertex_array) = 0;

    inline static API GetAPI() { return api; }

  private:
    static API api;    
  };
};