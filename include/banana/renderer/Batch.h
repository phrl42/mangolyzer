#pragma once 
#include "utils/incs.h"

#include "renderer/Type.h"

#include "game/Entity.h"

namespace banana
{

  struct BufferType
  {
    BufferType(BufferTypeIdent buftid)
    {
      std::unique_ptr<Type>type = Type::GetType();
      TypeID = type->GetTypeVal(buftid);

      switch(buftid)
      {
        case FLOAT:
          Size = sizeof(float);
          break;

        case FLOAT2:
          Size = sizeof(float) * 2;
          break;

        case FLOAT3:
          Size = sizeof(float) * 3;
          break;

        case FLOAT4:
          Size = sizeof(float) * 4;
          break;

        case INT:
          Size = sizeof(int);
          break;

        case INT2:
          Size = sizeof(int) * 2;
          break;

        case INT3:
          Size = sizeof(int) * 3;
          break;

        case INT4:
          Size = sizeof(int) * 4;
          break;
      }

      if(buftid <= 3)
      {
        TypeSize = sizeof(float);
      }
      else if(buftid > 3)
      {
        TypeSize = sizeof(int);
      }

      Count = (buftid % 4) + 1;
    }
    size_t TypeSize = 0;
    size_t Size = 0;

    unsigned int Count = 0;

    int TypeID;
  };

  struct BufferElement
  {
    BufferElement(std::initializer_list<BufferType> buftype)
    {
      for(BufferType buf : buftype)
      {
        Types.push_back(buf);
        TypeSize += buf.TypeSize;
        Size += buf.Size;

        Count++;
      }
    }

    std::vector<BufferType> Types;

    size_t Size = 0;
    size_t TypeSize = 0;

    unsigned int Count = 0;
  }; 

  struct ShaderLayout
  {
    ShaderLayout(ShaderType shadertype)
    : Element(BufferElement({FLOAT}))
    {
      // basically set shader layout here
      switch(shadertype)
      {
        case ShaderType::RECTANGLE:
          Element = BufferElement({FLOAT3, FLOAT4, FLOAT2, INT});
          break;
        
        case ShaderType::TRIANGLE:
          break;
        
        case ShaderType::CIRCLE:
          break;

        case ShaderType::TEXT:
          break;

        default:
          break;
      }
    }
    BufferElement Element;
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

    std::vector<std::shared_ptr<game::Entity>> Entities;

    ShaderType type;
    ShaderLayout shaderLayout;

    std::map<std::string, unsigned int> ids;

    int ElementSize = 0;

  };

};