#pragma once
#include "_Banana.h"
#include "renderer/RendererAPI.h"

namespace Banana
{
  class Renderer 
  {
  public:

    static void Init();
    static void BeginScene();
    static void EndScene();

    static void Submit(const Shr<VertexArray>& vertex_array);

    inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

  private:
  };
};