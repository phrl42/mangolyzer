#include "TextComponent.h"
#include "Text.h"
#include "renderer/Renderer2D.h"

namespace Banana
{
  TextComponent::TextComponent(const std::string &text, int font_width, int font_height)
  {
    this->name = "TextComponent";
    this->font_width = font_width;
    this->font_height = font_height;

    ChangeText(text);
  }

  void TextComponent::OnUpdate(float dt, const Transform &transform)
  {
    Renderer2D::DrawQuad(transform.pos, transform.size, transform.color, transform.rotation, font_texture, transform.proj);
  }

  void TextComponent::ChangeText(const std::string& text)
  {
    font_texture = Texture2D::Create(Text::GetPixels(text), font_width, font_height);
  }

};