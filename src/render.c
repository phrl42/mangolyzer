#include "render.h"

SDL_Texture *testTexture;

SDL_Rect srcrect;

// one needs to call initIMG()
SDL_Texture* renderImageLoadTexture(const char* file)
{
  testTexture = IMG_LoadTexture(rend, file);
  if(!testTexture)
  {
    errorHandling("Failed to load Texture: ", 1);
    return testTexture;
  }
  SDL_DestroyTexture(testTexture);
  return IMG_LoadTexture(rend, file);
}

void renderImageRenderTexture(SDL_Texture *texture, int x, int y, int w, int h)
{
  srcrect.x = x;
  srcrect.y = y;
  srcrect.w = w;
  srcrect.h = h;
  SDL_RenderCopy(rend, texture, NULL, &srcrect);
}

void renderClear()
{
  SDL_RenderClear(rend);
}

void renderPresent()
{
  SDL_RenderPresent(rend);
}
