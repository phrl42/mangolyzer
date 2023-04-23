#include "renderer/Renderer.h"
#include <SDL2/SDL_render.h>
#include "renderer/Shader.h"

namespace banana
{
  struct RenderStruct
  {
    const unsigned int GENERAL = 0;

    std::vector<std::shared_ptr<Shader>> Shaders;
    
    std::shared_ptr<Shader> generalShader = Shader::GetShader();
    
    RenderStruct()
    {
      Shaders.push_back(generalShader);
    };

  };
  
  RenderStruct renderInfo = RenderStruct();

  void Renderer::Init()
  {
    renderInfo.Shaders[renderInfo.GENERAL]->LoadShader("src/shader/default.glsl");
    renderInfo.Shaders[renderInfo.GENERAL]->Compile();
  }

  void Renderer::Render()
  {

  }

  // todo: get a better idea on how to do this
  void Renderer::AddRectangle(float x, float y, float w, float h, float r, float g, float b, Projection mode)
  {
    // bottom left:
/*
    // coords
    renderInfo.generalShader->vertex.push_back(x);
    renderInfo.generalShader->vertex.push_back(y - h);
    renderInfo.generalShader->vertex.push_back(0.0f);

    // colors
    renderInfo.generalShader->vertex.push_back(r);
    renderInfo.generalShader->vertex.push_back(g);
    renderInfo.generalShader->vertex.push_back(b);
    
    // texcoords
    renderInfo.generalShader->vertex.push_back(0);
    renderInfo.generalShader->vertex.push_back(0);

    // bottom right:
    renderInfo.generalShader->vertex.push_back(x + h);
    renderInfo.generalShader->vertex.push_back(y - h);
    renderInfo.generalShader->vertex.push_back(0.0f);

    renderInfo.generalShader->vertex.push_back(r);
    renderInfo.generalShader->vertex.push_back(g);
    renderInfo.generalShader->vertex.push_back(b);

    renderInfo.generalShader->vertex.push_back(0);
    renderInfo.generalShader->vertex.push_back(1);

    // top left (actual placement):
    renderInfo.generalShader->vertex.push_back(x);
    renderInfo.generalShader->vertex.push_back(y);
    renderInfo.generalShader->vertex.push_back(0.0f);

    renderInfo.generalShader->vertex.push_back(r);
    renderInfo.generalShader->vertex.push_back(g);
    renderInfo.generalShader->vertex.push_back(b);

    renderInfo.generalShader->vertex.push_back(0);
    renderInfo.generalShader->vertex.push_back(1);

    // top right:
    renderInfo.generalShader->vertex.push_back(x + w);
    renderInfo.generalShader->vertex.push_back(y);
    renderInfo.generalShader->vertex.push_back(0.0f);

    renderInfo.generalShader->vertex.push_back(r);
    renderInfo.generalShader->vertex.push_back(g);
    renderInfo.generalShader->vertex.push_back(b);

    renderInfo.generalShader->vertex.push_back(1);
    renderInfo.generalShader->vertex.push_back(1);

    // element buffer
    renderInfo.generalShader->element.push_back(renderInfo.generalShader->elementValue + 0);
    renderInfo.generalShader->element.push_back(renderInfo.generalShader->elementValue + 1);
    renderInfo.generalShader->element.push_back(renderInfo.generalShader->elementValue + 2);

    renderInfo.generalShader->element.push_back(renderInfo.generalShader->elementValue + 1);
    renderInfo.generalShader->element.push_back(renderInfo.generalShader->elementValue + 2);
    renderInfo.generalShader->element.push_back(renderInfo.generalShader->elementValue + 3);
    
    renderInfo.generalShader->elementValue += 4;

    */
  }
};