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

void initObjects(void)
{
 
  BananaRectangle objectOne;
  
  objectOne.x = 0.0f;
  objectOne.y = 0.0f;
  objectOne.w = 0.3f;
  objectOne.h = 0.3f;

  objectOne.r = 0.234230f;
  objectOne.g = 0.5f;
  objectOne.b = -1.0f;
  objectOne.proj = PERSPECTIVE;
  addRectangle(&objectOne);

  BananaTexture texOne;
  
  texOne.x = -1.0f;
  texOne.y = 1.0f;
  texOne.w = 1;
  texOne.h = 1;
  texOne.proj = PERSPECTIVE;
  texOne.path = "src/img/banana.png";
  addTexture(&texOne);

  BananaRectangle objectTwo;
  objectTwo.x = 0.5;
  objectTwo.y = -0.6;
  objectTwo.w = 0.4;
  objectTwo.h = 0.3;
  
  objectTwo.r = 0.4234234f;
  objectTwo.g = -0.32423f;
  objectTwo.b = 0.234234f;

  objectTwo.proj = PERSPECTIVE;
  addRectangle(&objectTwo);
}
float time = 0;
void loop(float frameTime)
{
  /*mat4 trans = GLM_MAT4_IDENTITY_INIT;
  if(time >= 1.0f)
  {
    time = 0.0f;
  }
  glm_rotate(trans, time * glm_rad(360), (vec3){0.0f, 0.0f, 1.0f});

  glUniformMatrix4fv(glGetUniformLocation(3, "transform"), 1, GL_FALSE, (float*)trans);
  time += frameTime;
*/


}
