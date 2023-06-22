#pragma once

#include "Banana.h"

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