#include "init.h"
#include "render.h"
#include "input.h"
#include "font.h"
int main()
{
  bool gameLoop = true; 

  int h = 500;
  int w = 500;
  int angle = 360;
  
  int WIDTH = 1920;
  int HEIGHT = 1080;

  initEngine(0);
  initWindow(WIDTH, HEIGHT, 0, 0, SDL_WINDOW_FULLSCREEN);
  initRenderer(0);
  initIMG(IMG_INIT_PNG);
  initTTF();

  SDL_Texture *consenbren;
  TTF_Font *font;
  SDL_Texture *fontTexture;
  SDL_Texture *banana;

  consenbren = renderImageLoadTexture("src/img/con.png");
  banana = renderImageLoadTexture("src/img/banana.png");
  
  font = fontLoad("src/ttf/mononoki.ttf", 16);

  fontTexture = fontRenderLoadFont(font, "test", 255, 255, 255, 255);
  
  while(gameLoop)
  {
    // quit when q is pressed
    if(inputHandleKeyboard() == SDLK_q) gameLoop = false;
  
    // clear screen
    renderClear();
   
    // animate honecker and the banana
    renderDisplayTextureFlip(consenbren, 100, 200, w, h, angle, -1);
    renderDisplayTextureFlip(banana, WIDTH / 2, 200, w, h, angle, SDL_FLIP_VERTICAL);
    renderDisplayTexture(fontTexture, (WIDTH / 2) - 100, 100, 100, 40);
    if(angle >= 360)
    {
      angle = 0;
    }
    angle += 10;

    // switch back- with frontbuffer
    renderPresent();
  }
  initDestroyTexture(consenbren);
  initDestroyTexture(banana);
  initQuit();
  return 0;
}
