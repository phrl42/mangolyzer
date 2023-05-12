#pragma once
#include "utils/incs.h"


namespace banana
{
  enum BufferTypeIdent {FLOAT = 0, FLOAT2, FLOAT3, FLOAT4, INT, INT2, INT3, INT4};
 
  struct Type
  {
    virtual ~Type() = default;

    static std::unique_ptr<Type> GetType();

    virtual int GetTypeVal(BufferTypeIdent buft) = 0;
  };
};