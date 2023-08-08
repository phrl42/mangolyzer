#include "Text.h"
namespace Banana
{
  
  void Text::Init(const std::string &font_path)
  {
    std::basic_ifstream<char> ifs(font_path);
    
    std::string content((std::istreambuf_iterator<char>(ifs)),
            (std::istreambuf_iterator<char>()));

    
  }

};