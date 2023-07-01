#include "_Banana.h"
#include "platform/OpenGL/OpenGLBuffer.h"

#include "glad.h"
#include "GLFW/glfw3.h"

namespace Banana
{
  OpenGLVertexBuffer::OpenGLVertexBuffer(const BufferLayout& layout, uint32_t size)
  : layout(layout)
  {
    glCreateBuffers(1, &id);

    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);

  }

  OpenGLVertexBuffer::~OpenGLVertexBuffer()
  {
    glDeleteBuffers(1, &id);
  }

  void OpenGLVertexBuffer::Bind()
  {
    glBindBuffer(GL_ARRAY_BUFFER, id);
  }

  void OpenGLVertexBuffer::Unbind()
  {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }



  OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
  : count(count)
  {
    glCreateBuffers(1, &id);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_DYNAMIC_DRAW);
  }

  void OpenGLIndexBuffer::Bind()
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
  }

  void OpenGLIndexBuffer::Unbind()
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); 
  }

  OpenGLIndexBuffer::~OpenGLIndexBuffer()
  {
    glDeleteBuffers(1, &id);
  }

};