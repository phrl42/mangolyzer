#pragma once 
#include "_Banana.h"

namespace Banana
{
  class Layer
  {
  public:
    Layer(const std::string& name = "Layer");

    virtual ~Layer() = default;

    virtual void OnAttach() = 0;
    virtual void OnDetach() = 0;

    virtual void OnUpdate() = 0;
    virtual void OnEvent(Event& event) = 0;

    inline const std::string& GetName() { return name; }
  
  private:
    std::string name;
  };
};