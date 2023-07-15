#pragma once

#include "Banana.h"
#include "renderer/Texture.h"

namespace SANDBOX
{
  class TestLayer : public Banana::Layer
  {
  public:
    TestLayer(const std::string& name = "Layer");
    
    ~TestLayer() override;

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    virtual void OnUpdate(float dt) override;
    virtual void OnEvent(Banana::Event& event) override;

    virtual void ImguiRender() override;

    virtual inline std::string& GetName() override { return name; }

    bool OnWindowResize(Banana::WindowResizeEvent& e);
  
  private:
    Banana::Shr<Banana::Texture2D> banana_tex;
    Banana::Shr<Banana::Texture2D> mango_tex;
    std::string name;
    Banana::Camera cam;
  };

};