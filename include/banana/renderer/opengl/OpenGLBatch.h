#pragma once 
#include "renderer/Batch.h"

namespace banana
{
  class OpenGLBatch : public Batch
  {
  public:
    ~OpenGLBatch() override;
    OpenGLBatch();

    void Upload() override;
    void Bind() override;
    void Unbind() override;
    unsigned int ElementValue = 0;
    unsigned int vaoID;

    bool full = false;

    ShaderType type;

    std::vector<float> vertex;
    std::vector<unsigned int> element;

  private:
    unsigned int vboID;
    unsigned int eboID;
  };
};