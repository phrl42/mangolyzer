#include "Text.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

namespace Banana
{
  int Text::ascent, Text::descent, Text::lineGap, Text::x;
  float Text::scale;
  stbtt_fontinfo Text::font_info;
  
  void Text::Init(const std::string &font_path)
  {
    std::basic_ifstream<char> ifs(font_path);
    
    std::string content((std::istreambuf_iterator<char>(ifs)),
            (std::istreambuf_iterator<char>()));

    if(!stbtt_InitFont(&font_info, (const unsigned char*)content.data(), 0))
    {
      LOG("Could not init font");
    }
    
    stbtt_GetFontVMetrics(&font_info, &ascent, &descent, &lineGap);

    scale = stbtt_ScaleForPixelHeight(&font_info, 120);

    ascent *= scale;
  }

  unsigned char* Text::GetPixels(const std::string& text)
  {    
        auto pixels = std::make_unique<unsigned char[]>(1024 * 1024);
    for (size_t i = 0; i < text.size(); ++i)
    {
      int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

      LOG(Text::font_info.numGlyphs);
      LOG(text[i]);
      LOG(Text::scale);

      if (!stbtt_FindGlyphIndex(&Text::font_info, text[i])) 
      {
        LOG("Found invalid character");
        continue;
      }

      stbtt_GetCodepointBitmapBox(&Text::font_info, text[i], Text::scale, Text::scale, &x1, &y1, &x2, &y2);
      LOG("criminal");
      auto y = Text::ascent + y1;
  
      int byteOffset = Text::x + y  * 1024;
      stbtt_MakeCodepointBitmap(&Text::font_info, pixels.get() + byteOffset, x2 - x1, y2 - y1, 1024, Text:: scale, Text::scale, text[i]);

      int ax = 0;
      stbtt_GetCodepointHMetrics(&Text::font_info, text[i], &ax, nullptr);
      Text::x += ax * Text::scale;

      if (i != text.size() - 1)
      {
          auto kern = stbtt_GetCodepointKernAdvance(&Text::font_info, text[i], text[i + 1]);
          Text::x += kern * Text::scale;
      }
    }
    Text::x = 0;
    return pixels.get();
  }

};