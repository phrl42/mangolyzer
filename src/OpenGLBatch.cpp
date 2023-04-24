#include "renderer/opengl/OpenGLBatch.h"

#ifdef MACRO_SDL2
#define GL_GLEXT_PROTOTYPES

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#endif

namespace banana
{
  OpenGLBatch::OpenGLBatch()
  {
    // create vao stuff
    glGenVertexArrays(1, &vaoID);
    
    glGenBuffers(1, &vboID);
    glGenBuffers(1, &eboID);
  }

  OpenGLBatch::~OpenGLBatch()
  {

  }

  void OpenGLBatch::Bind()
  {
    glBindVertexArray(vaoID);
  }
  
  void OpenGLBatch::Unbind()
  {
    glBindVertexArray(0);
  }

  void OpenGLBatch::Upload()
  {
    glBindVertexArray(vaoID);

    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    
    // upload vertices
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex.size()-1, vertex.data(), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
    
    // upload elements
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * element.size()-1, element.data(), GL_DYNAMIC_DRAW);  

    // tell opengl how to interpret our arrays
    
    // [check for ShaderType] !!!
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float) + sizeof(int),(void*)0);
    // enable vertex attribute (searching for vertices in the array, starting from 0)
    // make the connection between the vertices array and the vbo
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float) + sizeof(int), (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float) + sizeof(int), (void*)(sizeof(float) * 6));
    glEnableVertexAttribArray(2);
  
    glVertexAttribPointer(3, 1, GL_INT, GL_FALSE, 8 * sizeof(float) + sizeof(int), (void*)(sizeof(float) * 8));
    glEnableVertexAttribArray(3);

    // unbind vbo
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // do not unbind ebo

    // unbind vao
    glBindVertexArray(0);
  }

};