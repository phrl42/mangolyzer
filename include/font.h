#ifndef __FONT_H__
#define __FONT_H__

#include "init.h"

TTF_Font* fontLoad(const char *file, int fontsize);

SDL_Texture* fontRenderLoadFont(TTF_Font *font, const char* text, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

#endif
