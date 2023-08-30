#include "scene/EntryScene.h"
#include "scene/layer/SampleLayer.h"
#include "scene/layer/FreqLayer.h"
#include "layer/Layer.h"

#include "renderer/Renderer2D.h"

#include "imgui/IMGUILayer.h"

namespace SANDBOX
{
  EntryScene::EntryScene(const std::string& name)
  :name(name)
  {
    layer_stack.PushLayer(new SampleLayer("SampleLayer"));
    layer_stack.PushLayer(new FreqLayer("FreqLayer"));
  }

  void EntryScene::OnAttach()
  {
    AttachLayer();
  }

  void EntryScene::OnUpdate(float dt)
  {
    static float x = 14.3;
    static float y = 12.8;
    static float z = 15.1;

    if(Banana::Input::IsKeyPressed(KEY_S))
    {
      y -= 10 * dt;
    }
    
    if(Banana::Input::IsKeyPressed(KEY_W))
    {
      y += 10 * dt;
    }
    
    if(Banana::Input::IsKeyPressed(KEY_A))
    {
      x -= 10 * dt;
    }

    if(Banana::Input::IsKeyPressed(KEY_D))
    {
      x += 10 * dt;
    }

    if(Banana::Input::IsKeyPressed(KEY_T))
    {
      z += 10 * dt;
    }

    if(Banana::Input::IsKeyPressed(KEY_G))
    {
      z -= 10 * dt;
    }

    cam.SetPosition({x, y, z});

    if(Banana::IMGUILayer::active_layer == 0)
    {
      RenderLayer(dt, "SampleLayer");
    }
    else if(Banana::IMGUILayer::active_layer == 1)
    {
      RenderLayer(dt, "FreqLayer");
    }
  }

  void EntryScene::OnDetach()
  {
    DetachLayer();
  }
};
