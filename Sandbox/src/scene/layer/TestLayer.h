#pragma once

#include "Banana.h"
#include "renderer/Texture.h"

#define ARR_SIZE 900

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

    virtual inline std::string& GetName() override { return name; }
  
  private:
    Banana::Entity2D bananas[ARR_SIZE];
    std::string name;
  };

};