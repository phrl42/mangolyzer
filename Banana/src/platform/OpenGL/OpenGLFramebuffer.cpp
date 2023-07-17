#include "platform/OpenGL/OpenGLFramebuffer.h"

#include "glad.h"
#include "GLFW/glfw3.h"

namespace Banana
{
  OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferProperties& fb)
  : specs(fb)
  {
    Invalidate();
  }

  void OpenGLFramebuffer::Invalidate()
  {
    glCreateFramebuffers(1, &id);
    Bind();

    glCreateTextures(GL_TEXTURE_2D, 1, &color_id);
    //glTexImage2D();
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