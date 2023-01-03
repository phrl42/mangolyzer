// including twice does not matter, as we are using ifndef's
// it just makes it easier to read
#include "game.h"
#include "init.h"
#include "misc.h"
#include "render.h"

int init(void)
{
  // create an instance of our window
  BananaWindow window;

  // initialize our engine
  if(initEngine(0) == -1) return -1;

  // initialize our struct
  window.w = 800;
  window.h = 800;
  window.title = "";
  window.flags = SDL_WINDOW_OPENGL;

  // create a window and with it's context
  // pass the address of window, otherwise it would copy our instance, which would result in no changes
  if(initBWindow(&window) == -1) return -1;
  // one does not have to call setActiveWindow when only using one window
  // if you want to use a different window, call setActiveWindow and pass your window number
  // (starting from 0)
  return 0;
} 
int initObjects(void)
{
/* 
  BananaRectangle objectOne;
  
  objectOne.x = 0.0f;
  objectOne.y = 0.0f;
  objectOne.w = 0.3f;
  objectOne.h = 0.3f;

  objectOne.r = 1.0f;
  objectOne.g = 0.5f;
  objectOne.b = -1.0f;

  addRectangle(&objectOne);
 */
  BananaTexture texOne;
  
  texOne.x = -1.0f;
  texOne.y = 1.0f;
  texOne.w = 0.5f;
  texOne.h = 0.5f;

  texOne.path = "src/img/banana.png";
  addTexture(&texOne);
  return 0;
}
void loop(Uint64 frameTime)
{

}
