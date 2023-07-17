#pragma once
#include "_Banana.h"

namespace Banana
{
  struct FramebufferProperties
  {
    uint32_t width;
    uint32_t height;
  };

  class Framebuffer
  {
  public:
    virtual ~Framebuffer() = default;

    virtual void Shutdown() = 0;
    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    static Shr<Framebuffer> Create(const FramebufferProperties& fb);
  };
};