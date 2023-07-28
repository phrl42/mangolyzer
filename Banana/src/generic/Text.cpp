#include "Text.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

namespace Banana
{

  int Text::ascent, Text::descent, Text::lineGap, Text::x;
  float Text::scale;
  const stbtt_fontinfo *Text::font_info;
  
  void Text::Init(const std::string &font_path)
  {
    std::basic_ifstream<char> ifs(font_path);
    
    std::string content((std::istreambuf_iterator<char>(ifs)),
            (std::istreambuf_iterator<char>()));

    stbtt_fontinfo fontInfo;
    stbtt_InitFont(&fontInfo, (const unsigned char*)content.data(), 0);

    
    stbtt_GetFontVMetrics(&fontInfo, &ascent, &descent, &lineGap);

    scale = stbtt_ScaleForPixelHeight(&fontInfo, 120);

    ascent *= scale;
  }
};