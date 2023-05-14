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
      btch->ElementSize = 0;
    }

    game::Entity::EntityVector.clear();
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
          float y_offset = 0;
          float x_offset = 0;

          for(size_t i = 0; i < 4; i++)
          {
            switch(i)
            {
              case 0:
                // bottom left
                x_offset = 0;
                y_offset = 0;
                break;

              case 1:
                // bottom right
                x_offset = ent->w;
                y_offset = 0;
                break;

              case 2:
                // top left
                x_offset = 0;
                y_offset = ent->h;
                break;

              case 3:
                // top right
                x_offset = ent->w;
                y_offset = ent->h;
                break;

              default:
                break;
            }
            ent->vertex.push_back(ent->x + x_offset);
            ent->vertex.push_back(ent->y + y_offset);
            ent->vertex.push_back(0.0f);

            ent->vertex.push_back(ent->r);
            ent->vertex.push_back(ent->g);
            ent->vertex.push_back(ent->b);
            ent->vertex.push_back(ent->a);

            ent->vertex.push_back(0);
            ent->vertex.push_back(0);

            ent->vertex.push_back(-1);
          }
          // element buffer
          ent->element.push_back(renderInfo.ElementValue + 0);
          ent->element.push_back(renderInfo.ElementValue + 1);
          ent->element.push_back(renderInfo.ElementValue + 2);

          ent->element.push_back(renderInfo.ElementValue + 1);
          ent->element.push_back(renderInfo.ElementValue + 2);
          ent->element.push_back(renderInfo.ElementValue + 3);

          renderInfo.ElementValue += 4;
          btch->ElementSize += 6;
        }
      }
    }
  }
};
