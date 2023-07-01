#include "renderer/Renderer.h"
#include "renderer/RenderCommand.hpp"

namespace Banana
{

  void Renderer::Init()
  {
    RenderCommand::Init();
  }

  void Renderer::BeginScene()
  {

  }

  void Renderer::EndScene()
  {

  }

  void Renderer::Submit(const Shr<VertexArray>& vertex_array)
  {
    RenderCommand::DrawIndexed(vertex_array);
  }

};