#pragma once
#include "_Banana.h"

#include "renderer/RendererAPI.h"

// the rendercommand only dispatches

namespace Banana
{
  class RenderCommand
  {
  public:
    inline static void DrawIndexed(const Shr<VertexArray>& vertex_array, uint32_t index_count = 0) { api->DrawIndexed(vertex_array, index_count); }
    inline static void Clear() { api->Clear(); }
    inline static void SetClearColor(const glm::vec4& color) { api->SetClearColor(color); }
    inline static void Init() {api->Init();}

    inline static void SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height) { api->SetViewPort(x, y, width, height); }

  private:
    static RendererAPI* api;
  };

};