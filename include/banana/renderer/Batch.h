#pragma once 
#include "utils/incs.h"

namespace banana
{
  enum class ShaderType {TRIANGLE = 0, RECTANGLE, CIRCLE, TEXT};

  struct Batch
  {
    Batch()
    {
      this->ids["vaoID"] = 0;
      this->ids["vboID"] = 0;
      this->ids["eboID"] = 0;
    };
    std::vector<float> vertex;
    std::vector<unsigned int> element;

    ShaderType type;
    
    unsigned int ElementValue = 0;
    bool full = false;
    
    std::map<std::string, unsigned int> ids;
  };

};