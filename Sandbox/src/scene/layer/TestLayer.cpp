#include "scene/layer/TestLayer.h"

#include "renderer/Renderer2D.h"

#include "ecs/components/QuadComponent.h"

namespace SANDBOX
{
  TestLayer::TestLayer(const std::string& name)
  : name(name)
  {
    ent.transform.pos = {20, 20, 0};
    ent.transform.size = {10, 10, 0};
    //ent.transform.color = {1, 0.5, -1.0f, 1.0f};
    ent.transform.color = {1.0f, 1.0f, 1.0f, 1.0f};
    ent.transform.proj = Banana::Projection::PERSPECTIVE;

    ent.AddComponent(new Banana::QuadComponent("assets/textures/banana.png"));
    
  }

  TestLayer::~TestLayer()
  {

  }

  void TestLayer::OnAttach()
  {

  }

  void TestLayer::OnDetach()
  {
    
  }


  void TestLayer::OnEvent(Banana::Event& event)
  {
    
  }

  void TestLayer::OnUpdate(float dt)
  {
    if(Banana::Input::IsKeyPressed(KEY_Y))
    {
      ent.transform.pos.y += 2 * dt;
    }
    if(Banana::Input::IsKeyPressed(KEY_Z))
    {
      ent.transform.pos.y -= 2 * dt;
    }
    //ent.transform.rotation += 90 * dt;
    ent.Render(dt);
  }
};