#pragma once 
#include "utils/incs.h"

namespace banana
{
  enum class ShaderType {TRIANGLE = 0, RECTANGLE, CIRCLE, TEXT};

  class CBatch
  {
  public:
    static std::shared_ptr<Batch> GetBatch();
    
    virtual ~Batch() = default;

    virtual void Bind() = 0;
    virtual void Unbind() = 0;
    virtual void Upload(Batch batch) = 0;
    
    unsigned int ElementValue = 0;
    unsigned int vaoID;

  };
};