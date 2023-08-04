#include "Text.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

namespace Banana
{
  int Text::ascent, Text::descent, Text::lineGap, Text::x;
  float Text::scale;
  stbtt_fontinfo* Text::font_info;
  
  void Text::Init(const std::string &font_path)
  {
    std::basic_ifstream<char> ifs(font_path);
    
    std::string content((std::istreambuf_iterator<char>(ifs)),
            (std::istreambuf_iterator<char>()));

    stbtt_InitFont(font_info, (const unsigned char*)content.data(), 0);
    
    stbtt_GetFontVMetrics(font_info, &ascent, &descent, &lineGap);

    scale = stbtt_ScaleForPixelHeight(font_info, 120);

    ascent *= scale;
  }

  unsigned char* Text::GetPixels(const std::string& text)
  {
    auto pixels = std::make_unique<uint8_t[]>(1024 * 1024);

    const stbtt_fontinfo* test_bingus = Text::font_info;

    for (size_t i = 0; i < text.size(); ++i)
    {
      int x1, y1, x2, y2;
      stbtt_GetCodepointBitmapBox(test_bingus, text[i], Text::scale, Text::scale, &x1, &y1, &x2, &y2);

      auto y = Text::ascent + y1;
  
      int byteOffset = Text::x + y  * 1024;
      stbtt_MakeCodepointBitmap(test_bingus, pixels.get() + byteOffset, x2 - x1, y2 - y1, 1024, Text:: scale, Text::scale, text[i]);
  
      int ax = 0;
      stbtt_GetCodepointHMetrics(test_bingus, text[i], &ax, nullptr);
      Text::x += ax * Text::scale;

      if (i != text.size() - 1)
      {
          auto kern = stbtt_GetCodepointKernAdvance(test_bingus, text[i], text[i + 1]);
          Text::x += kern * Text::scale;
      }
    }
    Text::x = 0;
    return pixels.get();
  }

};