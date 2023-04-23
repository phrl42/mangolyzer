#pragma once
#include "utils/incs.h"

namespace banana
{

  class Shader 
  {
  protected:
    std::vector<float> vertex;
    std::vector<unsigned int> element;

    int elementValue = 0;
    
  public:

    virtual ~Shader() = default;
    virtual void LoadShader(std::string filepath) = 0;
    virtual void Compile() = 0;
    virtual void Bind() = 0;
    virtual void Unbind() = 0;

    static std::shared_ptr<Shader> GetShader();
  };

};