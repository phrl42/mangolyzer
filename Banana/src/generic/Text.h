#pragma once
#include "_Banana.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

namespace Banana
{
  class Text
  {
  public:
    Text() = default;

    static void Init(const std::string &font_path);

  public:
    static int ascent, descent, lineGap, x;

    static float scale;

    static const stbtt_fontinfo *font_info;
  };
};