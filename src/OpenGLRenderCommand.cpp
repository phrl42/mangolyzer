#include "renderer/opengl/OpenGLRenderCommand.h"

#ifdef MACRO_SDL2

#define GL_GLEXT_PROTOTYPES 1
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#endif

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
    
      //glUseProgram(shaderID);
    }

    // basically bind vao stuff
    glBindVertexArray(batch->ids["vaoID"]);
    glBindBuffer(GL_ARRAY_BUFFER, batch->ids["vboID"]);

    // upload vertices and elements
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * batch->vertex.size(), batch->vertex.data(), GL_DYNAMIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, batch->ids["eboID"], batch->element.data(), GL_DYNAMIC_DRAW);

    // specify order of data (based on the shader)

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float) + sizeof(int), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float) + sizeof(int), (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float) + sizeof(int), (void*)(sizeof(float) * 6));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 1, GL_INT, GL_FALSE, 8 * sizeof(float) + sizeof(int), (void*)(sizeof(float) * 8));
    glEnableVertexAttribArray(3);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    for(float& i : batch->vertex)
    {
      std::cout << i << " ";
    }
    std:: cout << std::endl;
  }

  void OpenGLRenderCommand::Draw(unsigned int elementOffset, ShaderType type)
  {
    // check for type
    // draw triangle
    glDrawElements(GL_TRIANGLES, elementOffset, GL_UNSIGNED_INT, 0);
  }
};