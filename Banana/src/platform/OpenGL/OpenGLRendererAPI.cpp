#include "platform/OpenGL/OpenGLRendererAPI.h"

#include "glad.h"
#include "GLFW/glfw3.h"

namespace Banana
{
  void OpenGLRendererAPI::Clear()
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
  {
    glClearColor(color.r, color.g, color.b, color.a);
  }

  void OpenGLRendererAPI::DrawIndexed(const Shr<VertexArray> &vertex_array)
  {
    vertex_array->Bind();
    glDrawElements(GL_TRIANGLES, vertex_array->GetElementBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
  }
};