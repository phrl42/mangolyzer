#include "platform/OpenGL/OpenGLFramebuffer.h"

#include "glad.h"
#include "GLFW/glfw3.h"

namespace Banana
{
  OpenGLFramebuffer::OpenGLFramebuffer()
  {
    glGenFramebuffers(1, &id);
    Bind();

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
      LOG("Could not create framebuffer");
      return;      
    }

  }


  OpenGLFramebuffer::~OpenGLFramebuffer()
  {
    Shutdown();
  }

  void OpenGLFramebuffer::Shutdown()
  {
    glDeleteFramebuffers(1, &id);
  }

  void OpenGLFramebuffer::Bind()
  {
    glBindFramebuffer(GL_FRAMEBUFFER, id);
  }

  void OpenGLFramebuffer::Unbind()
  {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }
};