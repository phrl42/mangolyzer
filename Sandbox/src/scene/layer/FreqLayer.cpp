#include "scene/layer/FreqLayer.h"

#include "renderer/Renderer2D.h"

#include "ecs/components/QuadComponent.h"
#include "ecs/components/TextComponent.h"

namespace SANDBOX
{
  FreqLayer::FreqLayer(const std::string& name)
    : name(name)
  {

  }

  FreqLayer::~FreqLayer()
  {

  }


  void FreqLayer::OnAttach()
  {
  }

  void FreqLayer::OnDetach()
  {
  }

  void FreqLayer::OnEvent(Banana::Event& event)
  {

  }

  void FreqLayer::OnUpdate(float dt)
  {
  }
};

