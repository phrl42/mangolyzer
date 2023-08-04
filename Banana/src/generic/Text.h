#pragma once
#include "_Banana.h"

struct stbtt_fontinfo;

namespace Banana
{
  class Text
  {
  public:
    Text() = default;

    static void Init(const std::string &font_path);

    static unsigned char* GetPixels(const std::string& text);

  public:
    static int ascent, descent, lineGap, x;

    static float scale;

    static stbtt_fontinfo* font_info;
  };
};