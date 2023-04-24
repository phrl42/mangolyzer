#pragma once 
#include "utils/incs.h"

namespace banana
{
  enum class ShaderType {TRIANGLE = 0, RECTANGLE, CIRCLE, TEXT};

  class Batch
  {
  public:
    static std::shared_ptr<Batch> GetBatch();
    
    virtual ~Batch() = default;

    virtual void Bind() = 0;
    virtual void Unbind() = 0;
    virtual void Upload() = 0;
    
    unsigned int ElementValue = 0;
    unsigned int vaoID;


    bool full = false;

    ShaderType type;

    std::vector<float> vertex;
    std::vector<unsigned int> element;
  };
};