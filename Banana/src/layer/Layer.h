#pragma once 
#include "_Banana.h"
#include "ecs/Entity.h"

namespace Banana
{
  class Layer
  {
  public:
    Layer(const std::string& name = "Layer");

    virtual ~Layer() = default;

    virtual void OnAttach() = 0;
    virtual void OnDetach() = 0;

    virtual void OnUpdate(float dt) = 0;
    virtual void OnEvent(Event& event) = 0;

    virtual std::string& GetName() = 0;

    void RenderEntity2D(Entity2D &ent);
  
  protected:
    std::string name;
  };
};