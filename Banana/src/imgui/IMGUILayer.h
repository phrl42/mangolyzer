#pragma once
#include "_Banana.h"
#include "layer/Layer.h"

namespace Banana
{

  class IMGUILayer : public Layer
  {
  public:
    IMGUILayer(const std::string& name = "IMGUILayer");

    virtual ~IMGUILayer() = default;

    virtual void OnAttach();
    virtual void OnDetach();

    virtual void OnUpdate();
    virtual void OnEvent(Event& event);

  private:
    std::string name;
    float l_time;
  };
};