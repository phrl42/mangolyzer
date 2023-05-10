#pragma once 
#include "utils/incs.h"

namespace banana
{
  enum class ShaderType {TRIANGLE = 0, RECTANGLE, CIRCLE, TEXT};

  struct ShaderLayout
  {
    ShaderLayout(ShaderType shadertype)
    {
      // basically set layout here
      switch(shadertype)
      {
        case ShaderType::TRIANGLE:
          break;
        
        case ShaderType::RECTANGLE:
          Layout.push_back(sizeof(float) * 3); //aPos
          Layout.push_back(sizeof(float) * 4); //aColor
          Layout.push_back(sizeof(float) * 2); //aTexCoords
          Layout.push_back(sizeof(int) * 1); //aTexID
          break;

        case ShaderType::CIRCLE:
          break;

        case ShaderType::TEXT:
          break;

        default:
          break;
      }
      for(size_t i = 0; i < Layout.size(); i++)
      {
        this->Size += Layout[i];
      }
    }
    
    size_t Size;
    std::vector<size_t> Layout;
  };


  struct Batch
  {
    Batch(ShaderType shadertype)
    : shaderLayout(shadertype)
    {
      this->ids["vaoID"] = 0;
      this->ids["vboID"] = 0;
      this->ids["eboID"] = 0;

      this->type = shadertype;
    };
    std::vector<float> vertex;
    std::vector<unsigned int> element;

    ShaderType type;
    
    unsigned int ElementValue = 0;
    bool full = false;
    
    std::map<std::string, unsigned int> ids;

    ShaderLayout shaderLayout;
  };

};