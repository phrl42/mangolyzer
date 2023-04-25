#pragma once 
#include "renderer/Batch.h"

namespace banana
{
  class OpenGLCBatch : public CBatch
  {
  public:
    ~OpenGLBatch() override;
    OpenGLBatch();

    void Upload() override;
    void Bind() override;
    void Unbind() override;
    unsigned int vaoID;

  private:
    unsigned int vboID;
    unsigned int eboID;
  };
};