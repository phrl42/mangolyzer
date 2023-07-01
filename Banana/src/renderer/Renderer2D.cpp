#include "renderer/Renderer2D.h"

#include "renderer/VertexArray.h"
#include "renderer/Shader.h"

namespace Banana
{

  struct Renderer2DStorage
  {
    Shr<VertexArray> vertex_array;
    Shr<Shader> shader;
    
  };

  static Renderer2DStorage* data;

  void Renderer2D::Init()
  {
    data = new Renderer2DStorage();

    data->vertex_array = VertexArray::Create();

    float squareVertices[5 * 4] =
    {
      -0.5f, -0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      0.5f, 0.5f, 0.0f,
      -0.5f, 0.5f, 0.0f
    };
    Shr<VertexBuffer> vertex_buffer;
    vertex_buffer = VertexBuffer::Create(squareVertices, sizeof(squareVertices));

    vertex_buffer->SetLayout({{ShaderDataType::Float3, "aPos"}});

    data->vertex_array->AddVertexBuffer(vertex_buffer);

    uint32_t squareIndices[6] = {0, 1, 2, 2, 3, 0};

    Shr<IndexBuffer> index_buffer = IndexBuffer::Create(squareIndices, sizeof(squareIndices));

    data->vertex_array->SetIndexBuffer(index_buffer);

    data->shader = Shader::Create("assets/shaders/default.glsl");

  }

  void Renderer2D::Shutdown()
  {
    delete data;
  }

  void Renderer2D::BeginScene()
  {

  }

  void Renderer2D::EndScene()
  {

  }

  void Renderer2D::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color)
  {

  }
};