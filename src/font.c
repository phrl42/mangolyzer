#include "font.h"
#include "init.h"

TTF_Font *fontTest;
SDL_Surface *surface;
SDL_Color color;
SDL_Texture *textureTest;


TTF_Font* fontLoad(const char* file, int fontsize)
{
  fontTest = TTF_OpenFont(file, fontsize);
  
  if(!fontTest)
  {
    errorHandling("Could not load Font: ", 3);
  }
  
  return fontTest;
}

SDL_Texture* fontRenderLoadFont(TTF_Font *font, const char* text, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
  color.r = r;
  color.g = g;
  color.b = b;
  color.a = a;

  // component values range from 0 to 255
  surface = TTF_RenderText_Solid(font, text, color);

  if(!surface)
  {
    errorHandling("Failed to RenderText_Solid: ", 3);
  }
  
  textureTest = SDL_CreateTextureFromSurface(rend, surface);

  SDL_FreeSurface(surface);
  if(!textureTest)
  {
    errorHandling("Failed to create Texture from Surface: ", 0);
    SDL_DestroyTexture(textureTest); // collapse
  }

  return textureTest;
}

void fontClose(TTF_Font *font)
{
  SDL_DestroyTexture(textureTest);
  TTF_CloseFont(font);
}
