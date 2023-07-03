#include "renderer/Renderer2D.h"

#include "renderer/VertexArray.h"
#include "renderer/Shader.h"

#include "renderer/RenderCommand.hpp"

namespace Banana
{
  struct QuadVertex
  {
    glm::vec3 position;
    glm::vec4 color;
    glm::vec2 tex_coords;
    // texid
  };

  struct Renderer2DStorage
  {
    const uint32_t MAX_QUADS = 10000;
    const uint32_t MAX_VERTICES = MAX_QUADS * 4;
    const uint32_t MAX_INDICES = MAX_QUADS * 6;
    
    Shr<VertexArray> quad_vertex_array;
    Shr<VertexBuffer> quad_vertex_buffer;
    Shr<Shader> shader;

    // quad batch
    uint32_t QuadIndexCount = 0;
    QuadVertex* quad_vertex_base = nullptr;
    QuadVertex* quad_vertex_ptr = nullptr;
  };

  static Renderer2DStorage data;

  void Renderer2D::Init()
  {
    // QUAD API STUFF
    data.quad_vertex_array = VertexArray::Create();

    data.quad_vertex_buffer = VertexBuffer::Create(
    {
      {ShaderDataType::Float3, "aPosition"},
      {ShaderDataType::Float4, "aColor"},
      {ShaderDataType::Float2, "aTexCoords"}
    }, sizeof(QuadVertex) * data.MAX_QUADS);

    data.quad_vertex_array->AddVertexBuffer(data.quad_vertex_buffer);
  
    data.quad_vertex_base = new QuadVertex[data.MAX_VERTICES];

    uint32_t *quad_indices = new uint32_t[data.MAX_INDICES];

    uint32_t offset = 0;
    for(int i = 0; i < data.MAX_INDICES; i += 6)
    {
      quad_indices[i + 0] = offset;
      quad_indices[i + 1] = offset + 1;
      quad_indices[i + 2] = offset + 2;

      quad_indices[i + 3] = offset + 1;
      quad_indices[i + 4] = offset + 2;
      quad_indices[i + 5] = offset + 3;

      offset += 4;
    }

    Shr<IndexBuffer> quad_index_buffer = IndexBuffer::Create(quad_indices, data.MAX_INDICES);
    data.quad_vertex_array->SetIndexBuffer(quad_index_buffer);
    delete[] quad_indices;

    data.shader = Shader::Create("assets/shaders/default.glsl");
    // maybe merge compile into create
    data.shader->Compile();
    
    data.shader->Bind();

    // INSERT OTHER GEOMETRY HERE
  }

  void Renderer2D::Shutdown()
  {
    delete[] data.quad_vertex_base;
  }

  void Renderer2D::BeginScene()
  {
    data.quad_vertex_ptr = data.quad_vertex_base;
    data.QuadIndexCount = 0;
  }

  void Renderer2D::EndScene()
  {
    uint32_t data_size = (uint8_t*)data.quad_vertex_ptr - (uint8_t*)data.quad_vertex_base;

    LOG(sizeof(QuadVertex));
    LOG(data_size);

    data.quad_vertex_buffer->SetData(data.quad_vertex_base, data_size);
    Flush();
  }

  void Renderer2D::Flush()
  {
    RenderCommand::DrawIndexed(data.quad_vertex_array, data.QuadIndexCount);
  }

  void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color)
  {
    // bottom left
    data.quad_vertex_ptr->position = pos;
    data.quad_vertex_ptr->color = color;
    data.quad_vertex_ptr->tex_coords = {0, 0};
    data.quad_vertex_ptr++;
    

    // bottom right
    data.quad_vertex_ptr->position = {pos.x + size.x, pos.y, pos.z};
    data.quad_vertex_ptr->color = color;
    data.quad_vertex_ptr->tex_coords = {1, 0};
    data.quad_vertex_ptr++;

    // top left
    data.quad_vertex_ptr->position = {pos.x, pos.y + size.y, pos.z};
    data.quad_vertex_ptr->color = color;
    data.quad_vertex_ptr->tex_coords = {0, 1};
    data.quad_vertex_ptr++;

    // top right
    data.quad_vertex_ptr->position = {pos.x + size.x, pos.y + size.y, pos.z};
    data.quad_vertex_ptr->color = color;
    data.quad_vertex_ptr->tex_coords = {1, 1};
    data.quad_vertex_ptr++;

    data.QuadIndexCount += 6;
  }
};