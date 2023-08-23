#include "scene/layer/TestLayer.h"

#include "renderer/Renderer2D.h"

#include "ecs/components/QuadComponent.h"
#include "ecs/components/TextComponent.h"

namespace SANDBOX
{
  TestLayer::TestLayer(const std::string& name)
  : name(name), sound(Banana::Sound("assets/sounds/menu.wav"))
  {
    ent.transform.pos = {0, 0, 1};
    ent.transform.size = {5, 5, 0};
    //ent.transform.color = {1, 0.5, -1.0f, 1.0f};
    ent.transform.color = {1.0f, 1.0f, 1.0f, 1.0f};
    ent.transform.proj = Banana::Projection::PERSPECTIVE;

    //ent.AddComponent(new Banana::QuadComponent("assets/textures/banana.png"));
    ent.AddComponent(new Banana::TextComponent("test"));
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
      ent.transform.size.y += 2 * dt;
    }
    if(Banana::Input::IsKeyPressed(KEY_Z))
    {
      ent.transform.size.x += 2 * dt;
    }
    
    if(Banana::Input::IsKeyPressed(KEY_J)) 
    {
      sound.StartSound();
      //Banana::TextComponent* texcomp = (Banana::TextComponent*)ent.GetComponent("TextComponent");
      //texcomp->ChangeText("salad bomb");
    }

    if(Banana::Input::IsKeyPressed(KEY_K) && !Banana::Input::IsKeyRepeat(KEY_K))
    {
      sound.ChangeSound("assets/sounds/test.wav");
    }

    //ent.transform.rotation += 90 * dt;
    //ent.transform.rotation += 90 * dt;
    ent.Render(dt);
  }
};
