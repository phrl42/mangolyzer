#pragma once
#include "renderer/Framebuffer.h"

namespace Banana
{
  class OpenGLFramebuffer : public Framebuffer
  {
  public:
    virtual ~OpenGLFramebuffer() override;

    OpenGLFramebuffer(const FramebufferProperties& fb);

    virtual void Shutdown() override;
    virtual void Bind() override;
    virtual void Unbind() override;

    virtual uint32_t GetColorAttachmentID() override;

    void Invalidate();
  private:
    uint32_t id;
    uint32_t color_id;
    uint32_t depth_id;
    FramebufferProperties specs;
  };
};