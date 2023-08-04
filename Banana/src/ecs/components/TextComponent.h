#pragma once
#include "_Banana.h"
#include "ecs/Component.h"
#include "renderer/Texture.h"

namespace Banana
{
  class TextComponent : public Component
  {
  public:
    virtual ~TextComponent() = default;

    TextComponent(const std::string& text, int font_width = 1024, int font_height = 1024);

    virtual void OnUpdate(float dt, const Transform& transform) override;

    void ChangeText(const std::string& text);
    
  private:
    Shr<Texture2D> font_texture;
    int font_width;
    int font_height;

  };
};