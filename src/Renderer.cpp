#include "renderer/Renderer.h"
#include "renderer/Shader.h"
#include "renderer/Batch.h"
#include "renderer/RenderCommand.h"

#define MAX_BATCH_SIZE 1000

namespace banana
{
  struct RenderStruct
  {
    // rendercommand configuration
    // rendercommand upload and rendercommand draw
    unsigned int RECTANGLEID = 0;    //unsigned int TRIANGLEID = 1;
    //unsigned int CIRCLEID = 2;
    //unsigned int TEXTID = 3;

    std::vector<std::shared_ptr<Shader>> Shaders;

    std::vector<std::shared_ptr<Batch>> Batches;

    std::shared_ptr<RenderCommand> renderCommand = RenderCommand::GetRenderCommand();
    
    RenderStruct()
    {
      // create shaders here
      std::shared_ptr<Shader> rectangleShader = Shader::GetShader();

      rectangleShader->Type = ShaderType::RECTANGLE;
      rectangleShader->LoadShader("src/shader/default.glsl");

      Shaders.push_back(rectangleShader);

      for(std::shared_ptr<Shader> shader : Shaders)
      {
        // compile each shader and assign a batch to each one
        shader->Compile();

        std::shared_ptr<Batch> btch = std::make_shared<Batch>();
        btch->type = shader->Type;
        Batches.push_back(btch);
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
    void SortBatches()
    {
      for(std::shared_ptr<Batch> batch : Batches)
      {
        if(batch->vertex.size() >= MAX_BATCH_SIZE)
        {
          batch->full = true;

          std::shared_ptr<Batch> btch = std::make_shared<Batch>();
          btch->type = batch->type;
          
          Batches.push_back(btch);
          // set shader use id
          SetID(batch->type, (unsigned int)(Batches.size() - 1));
        }

        if(batch->vertex.size() < MAX_BATCH_SIZE)
        {
          batch->full = false;
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
    for(std::shared_ptr<Batch> batch : renderInfo.Batches)
    {
      // load configuration, then send buffer to gpu
      // then draw
      for(std::shared_ptr<Shader> shader : renderInfo.Shaders)
      {
        if(batch->type == shader->Type)
        {
          // upload
          shader->Bind();
          renderInfo.renderCommand->Upload(batch);

          // draw
          renderInfo.renderCommand->Draw(batch->element.size()-1, shader->Type);
          //batch->Unbind();
        }
      }
    }
  }

  // todo: get a better idea on how to do this
  void Renderer::AddRectangle(BananaRectangle& bRectangle)
  {
    renderInfo.SortBatches();
    
    // bottom left:
    // coords
    renderInfo.Batches[renderInfo.RECTANGLEID]->vertex.push_back(bRectangle.x);
    renderInfo.Batches[renderInfo.RECTANGLEID]->vertex.push_back(bRectangle.y - bRectangle.h);
    renderInfo.Batches[renderInfo.RECTANGLEID]->vertex.push_back(0.0f);


    // colors
    renderInfo.Batches[renderInfo.RECTANGLEID]->vertex.push_back(bRectangle.r);
    renderInfo.Batches[renderInfo.RECTANGLEID]->vertex.push_back(bRectangle.g);
    renderInfo.Batches[renderInfo.RECTANGLEID]->vertex.push_back(bRectangle.b);
    
    // texcoords
    renderInfo.Batches[renderInfo.RECTANGLEID]->vertex.push_back(0);
    renderInfo.Batches[renderInfo.RECTANGLEID]->vertex.push_back(0);

    // bottom right:
    renderInfo.Batches[renderInfo.RECTANGLEID]->vertex.push_back(bRectangle.x + bRectangle.h);
    renderInfo.Batches[renderInfo.RECTANGLEID]->vertex.push_back(bRectangle.y - bRectangle.h);
    renderInfo.Batches[renderInfo.RECTANGLEID]->vertex.push_back(0.0f);

    renderInfo.Batches[renderInfo.RECTANGLEID]->vertex.push_back(bRectangle.r);
    renderInfo.Batches[renderInfo.RECTANGLEID]->vertex.push_back(bRectangle.g);
    renderInfo.Batches[renderInfo.RECTANGLEID]->vertex.push_back(bRectangle.b);

    renderInfo.Batches[renderInfo.RECTANGLEID]->vertex.push_back(0);
    renderInfo.Batches[renderInfo.RECTANGLEID]->vertex.push_back(1);

    // top left (actual placement):
    renderInfo.Batches[renderInfo.RECTANGLEID]->vertex.push_back(bRectangle.x);
    renderInfo.Batches[renderInfo.RECTANGLEID]->vertex.push_back(bRectangle.y);
    renderInfo.Batches[renderInfo.RECTANGLEID]->vertex.push_back(0.0f);

    renderInfo.Batches[renderInfo.RECTANGLEID]->vertex.push_back(bRectangle.r);
    renderInfo.Batches[renderInfo.RECTANGLEID]->vertex.push_back(bRectangle.g);
    renderInfo.Batches[renderInfo.RECTANGLEID]->vertex.push_back(bRectangle.b);

    renderInfo.Batches[renderInfo.RECTANGLEID]->vertex.push_back(0);
    renderInfo.Batches[renderInfo.RECTANGLEID]->vertex.push_back(1);

    // top right:
    renderInfo.Batches[renderInfo.RECTANGLEID]->vertex.push_back(bRectangle.x + bRectangle.w);
    renderInfo.Batches[renderInfo.RECTANGLEID]->vertex.push_back(bRectangle.y);
    renderInfo.Batches[renderInfo.RECTANGLEID]->vertex.push_back(0.0f);

    renderInfo.Batches[renderInfo.RECTANGLEID]->vertex.push_back(bRectangle.r);
    renderInfo.Batches[renderInfo.RECTANGLEID]->vertex.push_back(bRectangle.g);
    renderInfo.Batches[renderInfo.RECTANGLEID]->vertex.push_back(bRectangle.b);

    renderInfo.Batches[renderInfo.RECTANGLEID]->vertex.push_back(1);
    renderInfo.Batches[renderInfo.RECTANGLEID]->vertex.push_back(1);

    // element buffer
    renderInfo.Batches[renderInfo.RECTANGLEID]->element.push_back(renderInfo.Batches[renderInfo.RECTANGLEID]->ElementValue + 0);
    renderInfo.Batches[renderInfo.RECTANGLEID]->element.push_back(renderInfo.Batches[renderInfo.RECTANGLEID]->ElementValue + 1);
    renderInfo.Batches[renderInfo.RECTANGLEID]->element.push_back(renderInfo.Batches[renderInfo.RECTANGLEID]->ElementValue + 2);

    renderInfo.Batches[renderInfo.RECTANGLEID]->element.push_back(renderInfo.Batches[renderInfo.RECTANGLEID]->ElementValue + 1);
    renderInfo.Batches[renderInfo.RECTANGLEID]->element.push_back(renderInfo.Batches[renderInfo.RECTANGLEID]->ElementValue + 2);
    renderInfo.Batches[renderInfo.RECTANGLEID]->element.push_back(renderInfo.Batches[renderInfo.RECTANGLEID]->ElementValue + 3);
    
    renderInfo.Batches[renderInfo.RECTANGLEID]->ElementValue += 4;
  }
};