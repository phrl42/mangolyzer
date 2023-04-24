#include "renderer/Renderer.h"
#include "renderer/Shader.h"

#define MAX_BATCH_SIZE 1000

namespace banana
{
  struct RenderStruct
  {
    unsigned int RECTANGLEID = 0;
    //unsigned int TRIANGLEID = 1;
    //unsigned int CIRCLEID = 2;
    //unsigned int TEXTID = 3;

    std::vector<std::shared_ptr<Shader>> Shaders;
    
    RenderStruct()
    {
      // create shaders here
      std::shared_ptr<Shader> rectangleShader = Shader::GetShader();

      rectangleShader->Type = ShaderType::RECTANGLE;
      rectangleShader->LoadShader("src/shader/default.glsl");

      Shaders.push_back(rectangleShader);

      for(std::shared_ptr<Shader> shader : Shaders)
      {
        shader->Compile();
      }
    };

    void SetID(ShaderType type, unsigned int vpos)
    {
      switch(type)
      {
        case ShaderType::RECTANGLE:
          RECTANGLEID = vpos;
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

    // manages the numbering of available shaders per batch
    void SortShaders()
    {
      for(std::shared_ptr<Shader> shader : Shaders)
      {
        if(shader->vertex.size() >= MAX_BATCH_SIZE)
        {
          shader->full = true;

          std::shared_ptr<Shader> shdr = Shader::GetShader();
          shdr->Type = shader->Type;
          shdr->LoadShader(shader->FilePath);
          
          shdr->Compile();
          
          Shaders.push_back(shdr);

          // set shader use id
          SetID(shader->Type, (unsigned int)(Shaders.size() - 1));
        }

        if(shader->vertex.size() < MAX_BATCH_SIZE)
        {
          shader->full = false;
        }
      }
    }

  };
  
  RenderStruct renderInfo = RenderStruct();

  void Renderer::Init()
  {

  }

  void Renderer::Render()
  {
    // every shader has it's own batch draw call
    for(std::shared_ptr<Shader> shader : renderInfo.Shaders)
    {
      // do rectangle draw call
      if(shader->Type == ShaderType::RECTANGLE)
      {
        // load configuration, then send buffer to gpu
        // then draw
      }

      // do triangle draw call
      if(shader->Type == ShaderType::TRIANGLE)
      {

      }

      // do circle draw call
      if(shader->Type == ShaderType::CIRCLE)
      {

      }

      // do text draw call
      if(shader->Type == ShaderType::TEXT)
      {

      }
    }
  }

  // todo: get a better idea on how to do this
  void Renderer::AddRectangle(BananaRectangle& bRectangle)
  {
    //renderInfo.SortShaders();
    
    // bottom left:
    // coords
    renderInfo.Shaders[renderInfo.RECTANGLEID]->vertex.push_back(bRectangle.x);
    renderInfo.Shaders[renderInfo.RECTANGLEID]->vertex.push_back(bRectangle.y - bRectangle.h);
    renderInfo.Shaders[renderInfo.RECTANGLEID]->vertex.push_back(0.0f);

    // colors
    renderInfo.Shaders[renderInfo.RECTANGLEID]->vertex.push_back(bRectangle.r);
    renderInfo.Shaders[renderInfo.RECTANGLEID]->vertex.push_back(bRectangle.g);
    renderInfo.Shaders[renderInfo.RECTANGLEID]->vertex.push_back(bRectangle.b);
    
    // texcoords
    renderInfo.Shaders[renderInfo.RECTANGLEID]->vertex.push_back(0);
    renderInfo.Shaders[renderInfo.RECTANGLEID]->vertex.push_back(0);

    // bottom right:
    renderInfo.Shaders[renderInfo.RECTANGLEID]->vertex.push_back(bRectangle.x + bRectangle.h);
    renderInfo.Shaders[renderInfo.RECTANGLEID]->vertex.push_back(bRectangle.y - bRectangle.h);
    renderInfo.Shaders[renderInfo.RECTANGLEID]->vertex.push_back(0.0f);

    renderInfo.Shaders[renderInfo.RECTANGLEID]->vertex.push_back(bRectangle.r);
    renderInfo.Shaders[renderInfo.RECTANGLEID]->vertex.push_back(bRectangle.g);
    renderInfo.Shaders[renderInfo.RECTANGLEID]->vertex.push_back(bRectangle.b);

    renderInfo.Shaders[renderInfo.RECTANGLEID]->vertex.push_back(0);
    renderInfo.Shaders[renderInfo.RECTANGLEID]->vertex.push_back(1);

    // top left (actual placement):
    renderInfo.Shaders[renderInfo.RECTANGLEID]->vertex.push_back(bRectangle.x);
    renderInfo.Shaders[renderInfo.RECTANGLEID]->vertex.push_back(bRectangle.y);
    renderInfo.Shaders[renderInfo.RECTANGLEID]->vertex.push_back(0.0f);

    renderInfo.Shaders[renderInfo.RECTANGLEID]->vertex.push_back(bRectangle.r);
    renderInfo.Shaders[renderInfo.RECTANGLEID]->vertex.push_back(bRectangle.g);
    renderInfo.Shaders[renderInfo.RECTANGLEID]->vertex.push_back(bRectangle.b);

    renderInfo.Shaders[renderInfo.RECTANGLEID]->vertex.push_back(0);
    renderInfo.Shaders[renderInfo.RECTANGLEID]->vertex.push_back(1);

    // top right:
    renderInfo.Shaders[renderInfo.RECTANGLEID]->vertex.push_back(bRectangle.x + bRectangle.w);
    renderInfo.Shaders[renderInfo.RECTANGLEID]->vertex.push_back(bRectangle.y);
    renderInfo.Shaders[renderInfo.RECTANGLEID]->vertex.push_back(0.0f);

    renderInfo.Shaders[renderInfo.RECTANGLEID]->vertex.push_back(bRectangle.r);
    renderInfo.Shaders[renderInfo.RECTANGLEID]->vertex.push_back(bRectangle.g);
    renderInfo.Shaders[renderInfo.RECTANGLEID]->vertex.push_back(bRectangle.b);

    renderInfo.Shaders[renderInfo.RECTANGLEID]->vertex.push_back(1);
    renderInfo.Shaders[renderInfo.RECTANGLEID]->vertex.push_back(1);

    // element buffer
    renderInfo.Shaders[renderInfo.RECTANGLEID]->element.push_back(renderInfo.Shaders[renderInfo.RECTANGLEID]->ElementValue + 0);
    renderInfo.Shaders[renderInfo.RECTANGLEID]->element.push_back(renderInfo.Shaders[renderInfo.RECTANGLEID]->ElementValue + 1);
    renderInfo.Shaders[renderInfo.RECTANGLEID]->element.push_back(renderInfo.Shaders[renderInfo.RECTANGLEID]->ElementValue + 2);

    renderInfo.Shaders[renderInfo.RECTANGLEID]->element.push_back(renderInfo.Shaders[renderInfo.RECTANGLEID]->ElementValue + 1);
    renderInfo.Shaders[renderInfo.RECTANGLEID]->element.push_back(renderInfo.Shaders[renderInfo.RECTANGLEID]->ElementValue + 2);
    renderInfo.Shaders[renderInfo.RECTANGLEID]->element.push_back(renderInfo.Shaders[renderInfo.RECTANGLEID]->ElementValue + 3);
    
    renderInfo.Shaders[renderInfo.RECTANGLEID]->ElementValue += 4;
  }
};