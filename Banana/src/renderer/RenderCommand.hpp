#pragma once
#include "_Banana.h"

#include "renderer/RendererAPI.h"

// the rendercommand only dispatches

namespace Banana
{
  class RenderCommand
  {
  public:
    inline static void DrawIndexed(const Shr<VertexArray>& vertex_array) { api->DrawIndexed(vertex_array); }
    inline static void Clear() { api->Clear(); }
    inline static void SetClearColor(const glm::vec4& color) { api->SetClearColor(color); }

  private:
    static RendererAPI* api;
  };

};