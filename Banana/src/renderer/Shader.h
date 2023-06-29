#pragma once
#include "_Banana.h"

namespace Banana
{
  class Shader 
  {
  public:
    virtual ~Shader() = default;

    virtual void Compile() = 0;
    virtual void Bind() = 0;
    virtual void Unbind() = 0;
    
    static Shr<Shader> Create(const std::string& file_path);
  };
};