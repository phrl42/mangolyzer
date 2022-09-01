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

void renderDisplayTexture(SDL_Texture *texture, int x, int y, int w, int h)
{
  srcrect.x = x;
  srcrect.y = y;
  srcrect.w = w;
  srcrect.h = h;
  SDL_RenderCopy(rend, texture, NULL, &srcrect);
}

void renderDisplayTextureFlip(SDL_Texture *texture, int x, int y, int w, int h, double angle, SDL_RendererFlip flag)
{
  // use -1 for autism
  /* flags may be these:
    SDL_FLIP_NONE
    SDL_FLIP_HORIZONTAL
    SDL_FLIP_VERTICAL
  */

  if(flag == (SDL_RendererFlip)-1)
  {
    flag = SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL;
  }
  srcrect.x = x;
  srcrect.y = y;
  srcrect.w = w;
  srcrect.h = h;
  SDL_RenderCopyEx(rend, texture, NULL, &srcrect, angle, NULL, flag);
}

void renderClear()
{
  SDL_RenderClear(rend);
}

void renderPresent()
{
  SDL_RenderPresent(rend);
}
