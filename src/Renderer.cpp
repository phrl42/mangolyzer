#include "renderer/Renderer.h"
#include "renderer/Shader.h"
#include "renderer/Batch.h"
#include "renderer/RenderCommand.h"

#include "game/Entity.h"

#define MAX_ENTITY_SIZE 100

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

    unsigned int ElementValue = 0;

    std::shared_ptr<RenderCommand> renderCommand = RenderCommand::GetRenderCommand();

    
    RenderStruct()
    {
      Init();
    };

    void Init()
    {
      // create shaders here
      std::shared_ptr<Shader> rectangleShader = Shader::GetShader();

      rectangleShader->Type = ShaderType::RECTANGLE;
      rectangleShader->LoadShader("src/shader/default.glsl");

      Shaders.push_back(rectangleShader);
      for(std::shared_ptr<Shader> shader : Shaders)
      {
        // compile each shader and assign a batch to each one
        //shader->Compile();
        std::shared_ptr<Batch> btch = std::make_shared<Batch>(shader->Type);
        Batches.push_back(btch);
      }

    }

    /*void SetID(ShaderType type, unsigned int vpos)
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
    }*/
    
    // manages the numbering of available shaders per batch
    void SortBatches()
    {
      for(std::shared_ptr<Batch> batch : Batches)
      {
        for(std::shared_ptr<game::Entity> ent : game::Entity::EntityVector)
        {
          if(batch->type == ent->type)
          {
            if(batch->Entities.size() >= MAX_ENTITY_SIZE)
            {
              std::shared_ptr<Batch> btch = std::make_shared<Batch>(batch->type);

              Batches.push_back(btch);
            }
            
            if(batch->Entities.size() < MAX_ENTITY_SIZE)
            {
              batch->Entities.push_back(ent);
            }

          }
        }
      }
    }
  };

  RenderStruct Renderer::renderInfo;
  
  void Renderer::Init()
  {
    for(std::shared_ptr<Shader> shader : renderInfo.Shaders)
    {
      shader->Compile();
    }
  }

  void Renderer::Render()
  {
    // fill renderer with data
    AddEntity();

    // every shader has it's own batch draw call
    for(std::shared_ptr<Batch> batch : renderInfo.Batches)
    {
      for(std::shared_ptr<Shader> shader : renderInfo.Shaders)
      {
        // load configuration, then send buffer to gpu
        // then draw
        if(batch->type == shader->Type)
        {
          // upload
          shader->Bind();
          renderInfo.renderCommand->Upload(batch);

          // draw
          renderInfo.renderCommand->Draw(batch->ElementSize, shader->Type);
          shader->Unbind();
        }
      }
    }
    // clear everything from renderer
    for(auto btch : renderInfo.Batches)
    {
      for(auto ent : btch->Entities)
      {
        ent->vertex.clear();
        ent->element.clear();
      }
      btch->Entities.clear();
      renderInfo.ElementValue = 0;
    }
  }

  // todo: get a better idea on how to do this
  void Renderer::AddEntity()
  {
    // first put entities to their belonging batches

    renderInfo.SortBatches();

    for(auto btch : renderInfo.Batches)
    {
      for(auto ent : btch->Entities)
      {
        if(btch->type == ShaderType::RECTANGLE)
        {
        /*for(size_t i = 0; i < 4; i++)
        {
          switch(i)
          {
            case 0:
              break;

            case 1:
              break;
            
            case 2:
              break;
            
            case 3:
              break;
          }
        }*/

        // do adding shit
    ent->vertex.push_back(ent->x);
    ent->vertex.push_back(ent->y - ent->h);
    ent->vertex.push_back(0.0f);


    // colors
    ent->vertex.push_back(ent->r);
    ent->vertex.push_back(ent->g);
    ent->vertex.push_back(ent->b);
    ent->vertex.push_back(ent->a);
    
    // texcoords
    ent->vertex.push_back(0);
    ent->vertex.push_back(0);

    ent->vertex.push_back(-1);

    // bottom right:
    ent->vertex.push_back(ent->x + ent->h);
    ent->vertex.push_back(ent->y - ent->h);
    ent->vertex.push_back(0.0f);

    ent->vertex.push_back(ent->r);
    ent->vertex.push_back(ent->g);
    ent->vertex.push_back(ent->b);
    ent->vertex.push_back(ent->a);

    ent->vertex.push_back(0);
    ent->vertex.push_back(1);

    ent->vertex.push_back(-1);

    // top left (actual placement):
    ent->vertex.push_back(ent->x);
    ent->vertex.push_back(ent->y);
    ent->vertex.push_back(0.0f);

    ent->vertex.push_back(ent->r);
    ent->vertex.push_back(ent->g);
    ent->vertex.push_back(ent->b);
    ent->vertex.push_back(ent->a);

    ent->vertex.push_back(0);
    ent->vertex.push_back(1);

    ent->vertex.push_back(-1);

    // top right:
    ent->vertex.push_back(ent->x + ent->w);
    ent->vertex.push_back(ent->y);
    ent->vertex.push_back(0.0f);

    ent->vertex.push_back(ent->r);
    ent->vertex.push_back(ent->g);
    ent->vertex.push_back(ent->b);
    ent->vertex.push_back(ent->a);

    ent->vertex.push_back(1);
    ent->vertex.push_back(1);

    ent->vertex.push_back(-1);

    // element buffer
    ent->element.push_back(renderInfo.ElementValue + 0);
    ent->element.push_back(renderInfo.ElementValue + 1);
    ent->element.push_back(renderInfo.ElementValue + 2);

    ent->element.push_back(renderInfo.ElementValue + 1);
    ent->element.push_back(renderInfo.ElementValue + 2);
    ent->element.push_back(renderInfo.ElementValue + 3);
    
    renderInfo.ElementValue += 4;
    btch->ElementSize += 4;
        }
      }
    }
    // bottom left:
    // coords
    /*
    */
  }
};