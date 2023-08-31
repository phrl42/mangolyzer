#pragma once

#include "Banana.h"
#include "Sandbox.h"

#define MAX_SIZE 5000

namespace SANDBOX
{
  class EntryScene : public Banana::Scene
  {
  public:
    EntryScene(const std::string& name);

    ~EntryScene() override = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    virtual void OnUpdate(float dt) override;

  public:
    static float samples[MAX_SIZE];
    static int sample_count;
    
  private:
    std::string name;
    ma_decoder decoder;
    ma_encoder encoder;
    ma_device device;
  };
};
