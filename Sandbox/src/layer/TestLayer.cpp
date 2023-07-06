#include "layer/TestLayer.h"
#include "Banana.h"

#include "renderer/Renderer2D.h"
#include "renderer/Texture.h"

namespace SANDBOX
{
  TestLayer::TestLayer(const std::string& name)
  : name(name), cam(Banana::Camera())
  {

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

    if(Banana::Input::IsKeyPressed(KEY_W))
    {
      y -= 1 * dt;
    }
    
    if(Banana::Input::IsKeyPressed(KEY_S))
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

    cam.SetPosition({x, y, 1});
    Banana::Renderer2D::BeginScene(cam);
      Banana::Renderer2D::DrawQuad({0, 0, 0}, {1.0f, 1.0f}, {0.5f, -0.5f, 1.0f, 1.0f}, Banana::Texture2D::Create("assets/textures/krauss.png"));
      Banana::Renderer2D::DrawQuad({-1.0f, -0.5f, 0}, {1.0f, 1.0f}, {0.5f, -0.5f, 1.0f, 1.0f}, Banana::Texture2D::Create("assets/textures/lamp.png"));
      Banana::Renderer2D::DrawQuad({-1.0, -1.0, 0}, {1.0f, 1.0f}, {0.5f, -0.5f, 1.0f, 1.0f});
    Banana::Renderer2D::EndScene();
  }

  void TestLayer::ImguiRender()
  {

  }
  
};