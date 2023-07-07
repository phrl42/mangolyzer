#pragma once
#include "renderer/Framebuffer.h"

namespace Banana
{
  class OpenGLFramebuffer : public Framebuffer
  {
  public:
    virtual ~OpenGLFramebuffer() override;

    OpenGLFramebuffer();

    virtual void Shutdown() override;
    virtual void Bind() override;
    virtual void Unbind() override;
  private:
    uint32_t id;
  };
};