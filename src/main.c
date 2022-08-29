#include "init.h"
#include "render.h"
#include "input.h"
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
  
  SDL_Texture *consenbren;
  SDL_Texture *banana;
  consenbren = renderImageLoadTexture("src/img/con.png");
  banana = renderImageLoadTexture("src/img/banana.png");
  while(gameLoop)
  {
    // quit when q is pressed
    if(inputHandleKeyboard() == SDLK_q) gameLoop = false;
  
    // clear screen
    renderClear();
   
    // animate honecker and the banana
    renderImageRenderTextureFlip(consenbren, 100, 200, w, h, angle, -1);
    renderImageRenderTextureFlip(banana, WIDTH / 2, 200, w, h, angle, SDL_FLIP_VERTICAL);
    if(angle >= 360)
    {
      angle = 0;
    }
    angle++;

    // switch back- with frontbuffer
    renderPresent();
  }
  initDestroyTexture(consenbren);
  initDestroyTexture(banana);
  initQuit();
  return 0;
}
