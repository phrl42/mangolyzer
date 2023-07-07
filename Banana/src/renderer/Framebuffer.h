#pragma once
#include "_Banana.h"

namespace Banana
{
  class Framebuffer
  {
  public:
    virtual ~Framebuffer() = default;

    virtual void Shutdown() = 0;
    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    static Shr<Framebuffer> Create();
  };
};