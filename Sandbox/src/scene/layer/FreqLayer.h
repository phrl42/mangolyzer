#pragma once

#include "Banana.h"
#include "renderer/Texture.h"
#include "generic/Sound.h"

#define QUADS 900

namespace SANDBOX
{
  class FreqLayer : public Banana::Layer
  {
  public:
    FreqLayer(const std::string& name = "FreqLayer");
    
    ~FreqLayer() override;

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    virtual void OnUpdate(float dt) override;
    virtual void OnEvent(Banana::Event& event) override;

    virtual inline std::string& GetName() override { return name; }
  
  private:
    Banana::Entity ent[QUADS];
    std::string name;
    ma_decoder decoder;
    ma_encoder encoder;
    ma_device device;
  };

};
