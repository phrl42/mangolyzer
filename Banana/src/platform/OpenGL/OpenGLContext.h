#pragma once
#include "renderer/Context.h"

namespace Banana
{
  class OpenGLContext : public Context
  {
  public:
    OpenGLContext();
    virtual ~OpenGLContext() override = default;

		virtual void Init() override;
		virtual void Shutdown() override;
		virtual void SwapBuffer() override;
  private:

  };
};