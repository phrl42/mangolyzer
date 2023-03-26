#pragma once

#include "utils/incs.h"

namespace banana
{
  class Window
  {
  public:
    virtual ~Window() = default;
    virtual void Init(std::string title, int width, int height) = 0;
    virtual void* GetWindow() = 0;

    static std::shared_ptr<Window> GetWindowWS();

    static std::vector<std::shared_ptr<Window>> Windows;

    static std::shared_ptr<Window> GetMostRecentWindow();

    glm::vec4 BackgroundColor = {0, 0, 0, 0};

  private:
  };
};