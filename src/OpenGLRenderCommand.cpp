#include "renderer/opengl/OpenGLRenderCommand.h"

#ifdef MACRO_SDL2
#include <SDL2/SDL.h>
#endif

#include "utils/glad.h"

#include "window/Window.h"

namespace banana
{

  OpenGLRenderCommand::OpenGLRenderCommand()
  {
    
  }

  OpenGLRenderCommand::~OpenGLRenderCommand()
  {
    
  }

  void OpenGLRenderCommand::Clear()
  {
    glClear(GL_COLOR_BUFFER_BIT);
  }

  void OpenGLRenderCommand::SetColor(glm::vec4 color)
  {
    glClearColor(color.r, color.g, color.b, color.a);
  }

  void OpenGLRenderCommand::Update(void* window)
  {
    switch(banana::Management::UsedWS)
    {
      case WindowingSystem::SDL2:
        SDL_GL_SwapWindow((SDL_Window*)window);
        break;
      default:
        break;
    }
  }

  void OpenGLRenderCommand::Upload(std::shared_ptr<Batch> batch)
  {
    // create vao layout based on shader layout
    if(!batch->ids["vaoID"])
    {
      glGenVertexArrays(1, &batch->ids["vaoID"]);
      glGenBuffers(1, &batch->ids["vboID"]);
      glGenBuffers(1, &batch->ids["eboID"]);
    }

    // bind vao
    glBindVertexArray(batch->ids["vaoID"]);

    // upload vbo
    glBindBuffer(GL_ARRAY_BUFFER, batch->ids["vboID"]);

    // please rework the renderer; this is is awful bullshit
    std::vector<float> vertices;

    for(std::shared_ptr<game::Entity> ent : batch->Entities)
    {
      for(auto vt : ent->vertex)
      {
        vertices.push_back(vt);
      }
    }

    std::vector<unsigned int> elements;
    for(std::shared_ptr<game::Entity> ent : batch->Entities)
    {
      for(auto el : ent->element)
      {
        elements.push_back(el);
      }
    }
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_DYNAMIC_DRAW);
    
    // upload ebo
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, batch->ids["eboID"]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * elements.size(), elements.data(), GL_DYNAMIC_DRAW);

    // specify order of data (based on the shader)

    size_t offset = 0;

    for(size_t i = 0; i < batch->shaderLayout.Element.Count; i++)
    {
      glVertexAttribPointer(i, batch->shaderLayout.Element.Types[i].Count, batch->shaderLayout.Element.Types[i].TypeID, GL_FALSE, batch->shaderLayout.Element.Size, (void*)offset);
      glEnableVertexAttribArray(i);

      offset += batch->shaderLayout.Element.Types[i].Size;
    }
    
  }

  void OpenGLRenderCommand::Draw(unsigned int elementOffset, ShaderType type)
  {
    // check for type
    // draw triangle
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_TRIANGLES, elementOffset, GL_UNSIGNED_INT, 0);    
  }
};