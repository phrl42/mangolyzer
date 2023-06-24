#pragma once 
#include "_Banana.h"

namespace Banana
{
  class Layer
  {
  public:
    Layer(const std::string& name = "Layer");

    virtual ~Layer() = default;

    virtual void OnAttach();
    virtual void OnDetach();

    virtual void OnUpdate();
    virtual void OnEvent(Event& event);

    inline const std::string& GetName() { return name; }
  
  private:
    std::string name;
  };
};