#ifndef __RENDER_H__
#define __RENDER_H__

#include "init.h"

SDL_Texture* renderImageLoadTexture(const char* file);

void renderImageRenderTexture(SDL_Texture *texture, int x, int y, int w, int h);

void renderClear();
void renderPresent();

#endif
