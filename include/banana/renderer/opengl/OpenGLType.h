#pragma once
#include "renderer/Type.h"

#include "utils/glad.h"

namespace banana
{
  struct OpenGLType : Type
  {
    OpenGLType()
    {

    }

    ~OpenGLType() override
    {

    }

    int GetTypeVal(BufferTypeIdent buft) override
    {
      if(buft <= 3)
      {
        return GL_FLOAT;
      }
      else if (buft > 3)
      {
        return GL_INT;
      }
    }
  };
};