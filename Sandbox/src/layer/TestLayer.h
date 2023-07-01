#pragma once

#include "Banana.h"


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
  
  private:
    std::string name;
  };

};