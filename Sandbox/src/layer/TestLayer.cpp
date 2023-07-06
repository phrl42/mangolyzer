#include "layer/TestLayer.h"
#include "Banana.h"

#include "renderer/Renderer2D.h"
#include "renderer/Texture.h"

namespace SANDBOX
{
  TestLayer::TestLayer(const std::string& name)
  : name(name), cam(Banana::Camera())
  {
    mango_tex = Banana::Texture2D::Create("assets/textures/bunny_stalin.jpg");
    banana_tex = Banana::Texture2D::Create("assets/textures/finito.png");
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
    //LOG(event.ToString());
  }

  void TestLayer::OnUpdate(float dt)
  {
    static float x = 0;
    static float y = 0;
    static float z = 0;

    static float banana_rotation = 0.0f;

    if(Banana::Input::IsKeyPressed(KEY_S))
    {
      y -= 1 * dt;
    }
    
    if(Banana::Input::IsKeyPressed(KEY_W))
    {
      y += 1 * dt;
    }
    
    if(Banana::Input::IsKeyPressed(KEY_A))
    {
      x -= 1 * dt;
    }

    if(Banana::Input::IsKeyPressed(KEY_D))
    {
      x += 1 * dt;
    }

    if(Banana::Input::IsKeyPressed(KEY_T))
    {
      z += 1 * dt;
    }

    if(Banana::Input::IsKeyPressed(KEY_G))
    {
      z -= 1 * dt;
    }

    banana_rotation += 90 * dt;  

    if(banana_rotation == 180)
    {
      banana_rotation = 0;
    }

    cam.SetPosition({x, y, z});
    // TODO: simplify drawquad functions
    // get some logic for it
    Banana::Renderer2D::BeginScene(cam);
      Banana::Renderer2D::DrawQuad({0, 0, 0}, {1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, banana_rotation, mango_tex);
      Banana::Renderer2D::DrawQuad({-1.0f, -0.5f, 0}, {1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, banana_rotation, banana_tex);
      //Banana::Renderer2D::DrawQuad({-1.0, -1.0, 0}, {1.0f, 1.0f}, {0.5f, -0.5f, 1.0f, 1.0f}, 0.0f, );
    Banana::Renderer2D::EndScene();
  }

  void TestLayer::ImguiRender()
  {

  }
  
};