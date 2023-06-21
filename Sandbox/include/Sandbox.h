#pragma once

#include "Banana.h"
#include "_sandbox.h"

namespace SANDBOX
{
  class Sandbox : public Banana::Application
  {
  public:
    Sandbox();

    void Run() override;

    ~Sandbox() override;
  };
};