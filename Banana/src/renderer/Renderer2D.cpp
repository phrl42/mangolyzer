#include "renderer/Renderer2D.h"

#include "renderer/VertexArray.h"
#include "renderer/Shader.h"

#include "renderer/RenderCommand.hpp"

#include "renderer/Texture.h"

#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

namespace Banana
{
  struct QuadVertex
  {
    glm::vec3 position;
    glm::vec4 color;
    glm::vec2 tex_coords;
    float projID;
    float texID;
  };

  struct Renderer2DStorage
  {
    static const uint32_t MAX_QUADS = 20000;
    static const uint32_t MAX_VERTICES = MAX_QUADS * 4;
    static const uint32_t MAX_INDICES = MAX_QUADS * 6;
		static const uint32_t MAX_TEXTURE_SLOTS = 32;

    Shr<VertexArray> quad_vertex_array;
    Shr<VertexBuffer> quad_vertex_buffer;
    Shr<Shader> shader;

    Camera scene_camera;

    // quad batch
    uint32_t QuadIndexCount = 0;
    QuadVertex* quad_vertex_base = nullptr;
    QuadVertex* quad_vertex_ptr = nullptr;

		std::array<Shr<Texture2D>, MAX_TEXTURE_SLOTS> TextureSlots;
		uint32_t TextureSlotIndex = 1; // 0 = white texture
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
      {ShaderDataType::Float2, "aTexCoords"},
      {ShaderDataType::Float, "aProjectionID"},
      {ShaderDataType::Float, "aTexID"}
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

    data.shader = Shader::Create("assets/shaders/quad.glsl");
    // maybe merge compile into create
    data.shader->Compile();
    
    // INSERT OTHER GEOMETRY HERE
  
    // uniform stuff
    int32_t samplers[data.MAX_TEXTURE_SLOTS];
		for (uint32_t i = 0; i < data.MAX_TEXTURE_SLOTS; i++)
			samplers[i] = i;
    data.shader->UploadIntArray("fTexture", data.MAX_TEXTURE_SLOTS, samplers);
  }

  void Renderer2D::Shutdown()
  {
    delete[] data.quad_vertex_base;
  }

  void Renderer2D::BeginScene(const Camera& cam)
  {
    data.scene_camera = cam;
    RenderCommand::Clear();
    StartBatch();
  }

  void Renderer2D::BeginScene()
  {
    LOG("Warning! Client did not specify a camera");
    data.scene_camera = Camera();
    RenderCommand::Clear();
    StartBatch();
  }

  void Renderer2D::StartBatch()
  {
    data.quad_vertex_ptr = data.quad_vertex_base;
    data.QuadIndexCount = 0;

    data.TextureSlotIndex = 0;

    // upload uniforms here
    data.shader->UploadMat4f("uPerspectiveViewProjection", data.scene_camera.GetPerspectiveViewProjection());
    data.shader->UploadMat4f("uOrthographicViewProjection", data.scene_camera.GetOrthographicViewProjection());
  }

  void Renderer2D::NextBatch()
  {
    Flush();
    StartBatch();
  }

  void Renderer2D::EndScene()
  {
    Flush();
  }

  void Renderer2D::Flush()
  {
    if(data.QuadIndexCount)
    {
      uint32_t data_size = (uint32_t)((uint8_t*)data.quad_vertex_ptr - (uint8_t*)data.quad_vertex_base);
      data.quad_vertex_buffer->SetData(data.quad_vertex_base, data_size);

			for (uint32_t i = 0; i < data.TextureSlotIndex; i++)
				data.TextureSlots[i]->Bind(i);

      data.shader->Bind();
      RenderCommand::DrawIndexed(data.quad_vertex_array, data.QuadIndexCount);
    }
  }

  void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color, float rotation, const Shr<Texture2D>& texture, Projection proj)
  {
    if(texture == nullptr)
    {
      LOG("Omitted nullptr texture in renderer: Please initialize your texture");
      return;
    }
    
		if (data.QuadIndexCount >= data.MAX_INDICES)
			NextBatch();
    
		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < data.TextureSlotIndex; i++)
		{
			if (*data.TextureSlots[i] == *texture)
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
      if(data.TextureSlotIndex >= data.MAX_TEXTURE_SLOTS)
        NextBatch();
      
			textureIndex = (float)data.TextureSlotIndex;
			data.TextureSlots[data.TextureSlotIndex] = texture;
			data.TextureSlotIndex++;
    }
    
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
    
    if(rotation)
    {
      transform = glm::translate(glm::mat4(1.0f), pos)
        * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
        * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
    }

    // bottom left
    data.quad_vertex_ptr->position = glm::vec4({pos, 1.0f});
    data.quad_vertex_ptr->color = color;
    data.quad_vertex_ptr->tex_coords = {0, 0};
    data.quad_vertex_ptr->projID = proj;
    data.quad_vertex_ptr->texID = textureIndex;
    data.quad_vertex_ptr++;
    
    // bottom right
    data.quad_vertex_ptr->position = glm::vec4({pos.x + size.x, pos.y, pos.z, 1.0f});
    data.quad_vertex_ptr->color = color;
    data.quad_vertex_ptr->tex_coords = {1.0f, 0.0f};
    data.quad_vertex_ptr->projID = proj;
    data.quad_vertex_ptr->texID = textureIndex;
    data.quad_vertex_ptr++;

    // top left
    data.quad_vertex_ptr->position = glm::vec4({pos.x, pos.y + size.y, pos.z, 1.0f});
    data.quad_vertex_ptr->color = color;
    data.quad_vertex_ptr->tex_coords = {0.0f, 1.0f};
    data.quad_vertex_ptr->projID = proj;
    data.quad_vertex_ptr->texID = textureIndex;
    data.quad_vertex_ptr++;

    // top right
    data.quad_vertex_ptr->position = glm::vec4({pos.x + size.x, pos.y + size.y, pos.z, 1.0f});
    data.quad_vertex_ptr->color = color;
    data.quad_vertex_ptr->tex_coords = {1.0f, 1.0f};
    data.quad_vertex_ptr->projID = proj;
    data.quad_vertex_ptr->texID = textureIndex;
    data.quad_vertex_ptr++;

    data.QuadIndexCount += 6;
  }

  void Renderer2D::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color, float rotation, Projection proj)
  {
    if (data.QuadIndexCount >= data.MAX_INDICES)
    {
      LOG(pos.x);
      NextBatch();
    }
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

    if(rotation)
    {
      transform = glm::translate(glm::mat4(1.0f), pos)
        * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
        * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
    }

    // bottom left
    data.quad_vertex_ptr->position = glm::vec4({pos, 1.0f});
    data.quad_vertex_ptr->color = color;
    data.quad_vertex_ptr->tex_coords = {0, 0};
    data.quad_vertex_ptr->projID = proj;
    data.quad_vertex_ptr->texID = -1;
    data.quad_vertex_ptr++;
    

    // bottom right
    data.quad_vertex_ptr->position = glm::vec4({pos.x + size.x, pos.y, pos.z, 1.0f});
    data.quad_vertex_ptr->color = color;
    data.quad_vertex_ptr->tex_coords = {1, 0};
    data.quad_vertex_ptr->projID = proj;
    data.quad_vertex_ptr->texID = -1;
    data.quad_vertex_ptr++;

    // top left
    data.quad_vertex_ptr->position = glm::vec4({pos.x, pos.y + size.y, pos.z, 1.0f});
    data.quad_vertex_ptr->color = color;
    data.quad_vertex_ptr->tex_coords = {0, 1};
    data.quad_vertex_ptr->projID = proj;
    data.quad_vertex_ptr->texID = -1;
    data.quad_vertex_ptr++;

    // top right
    data.quad_vertex_ptr->position = glm::vec4({pos.x + size.x, pos.y + size.y, pos.z, 1.0f});
    data.quad_vertex_ptr->color = color;
    data.quad_vertex_ptr->tex_coords = {1, 1};
    data.quad_vertex_ptr->projID = proj;
    data.quad_vertex_ptr->texID = -1;
    data.quad_vertex_ptr++;

    data.QuadIndexCount += 6;
  }
};
