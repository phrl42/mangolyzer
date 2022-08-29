#include "init.h"
#include "render.h"
#include "input.h"
int main()
{
  bool gameLoop = true;

  SDL_Texture *consenbren;

  initEngine(0);
  initWindow(1920, 1080, 0, 0, SDL_WINDOW_FULLSCREEN);
  initRenderer(0);
  initIMG(IMG_INIT_PNG);

  consenbren = renderImageLoadTexture("src/img/con.png");
  while(gameLoop)
  {
    // quit when q is pressed
    if(inputHandleKeyboard() == SDLK_q) gameLoop = false;
    // clear screen
    renderClear();
  
    renderImageRenderTexture(consenbren, 10, 10, 1000, 1009); 

    // switch back- with frontbuffer
    renderPresent();
  }
  initDestroyTexture(consenbren);
  initQuit();
  return 0;
}
