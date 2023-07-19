#include "scene/EntryScene.h"
#include "scene/layer/TestLayer.h"
#include "layer/Layer.h"

namespace SANDBOX
{
  EntryScene::EntryScene(const std::string& name)
  :name(name)
  {
    layer_stack.PushLayer(new TestLayer("Layer One"));
  }

  void EntryScene::OnAttach()
  {
    for(auto layer : layer_stack)
    {
      layer->OnAttach();
    }
  }

  void EntryScene::OnUpdate(float dt)
  {
    for(auto layer : layer_stack)
    {
      layer->OnUpdate(dt);
    }
  }

  void EntryScene::OnDetach()
  {
    for(auto layer : layer_stack)
    {
      layer->OnDetach();
    }
  }

};