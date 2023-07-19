#include "layer/Scene.h"

namespace Banana
{

  Scene::Scene(const std::string& name)
  : name(name), cam(Camera()) {}


  void Scene::PopLayer(Layer* layer)
  {
    layer_stack.PopLayer(layer);
  }

  void Scene::PushLayer(Layer* layer)
  {
    layer_stack.PushLayer(layer);
  }

  void Scene::PopOverlay(Layer* layer)
  {
    layer_stack.PopOverlay(layer);
  }

  void Scene::PushOverlay(Layer* layer)
  {
    layer_stack.PushOverlay(layer);
  }

  void Scene::OnEvent(Event& e)
  {
    for(auto it = layer_stack.end(); it != layer_stack.begin();)
    {
      (*--it)->OnEvent(e);

      if(e.handled)
      {
        break;
      }
    }
  }

};