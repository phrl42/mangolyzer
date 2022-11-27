#include "../include/init.h"
//#include "../include/render.h"
//#include "input.h" discarded for now
//#include "../include/font.h"
//#include "../include/mixer.h"
#define WIDTH 1920
#define HEIGHT 1080

int main(int argc, char* argv[])
{
  // this depends on the user
  //bool gameLoop = true; 
  //int angle = 360;

  // create a BananaWindow instance
  BananaWindow window;

  // initialize our engine
  if(initEngine(SDL_INIT_VIDEO) == -1) return -1;

  // initialize the struct..
  window.w = 500;
  window.h = 500;
  window.title = "...";
  window.flags = SDL_WINDOW_OPENGL;
  
  // this is where window.win gets initialized...
  // pass the address of window, otherwise it would copy our instance, which does not do anything
  initWindow(&window);
  bool troll = true;
  SDL_Event ev;
  int maximumFPS = 60;
  Uint64 ticks = 0;
  Uint64 frameTime = maximumFPS;
  char buffer[10];
  memset(buffer, '\0', sizeof(buffer) / sizeof(char));
  
  // set background color
  glClearColor(0.0, 0.0, 0.0, 0.0);
  while(troll)
  {
    // update elpased time 
    ticks = SDL_GetTicks64(); 
    
    // clear buffer
    glClear(GL_COLOR_BUFFER_BIT);
    while(SDL_PollEvent(&ev))
    {
      if(ev.type == SDL_QUIT)
      {
        troll = false;
      }
    }
    // draw triangle
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.5f, 0.0f);
    glVertex2f(0.0f, 1.0f);
    glVertex2f(0.5f, 0.0f);
    glEnd();

    // reload the screen
    SDL_GL_SwapWindow(window.win);
    // calculate the time of one frame
    // basically, we set v-sync to true, so let's say our frameTime gets capped to
    // 60 fps, we count the time of one frame 
    // the result will always be 0, if it does not use much resources
    // but 0 is 60fps in our case, because it displays 60 frames per second, without waiting
    // if we were to process something, one frame will take longer, which then results in lower
    // frames per second, so we subtract the value of frameTime and divide it with 60 because
    // we calculate on frame time for 60 seconds..
    frameTime = frameTime - ((SDL_GetTicks64() - ticks) / 60);
    if(frameTime == 60)
    {
      sprintf(buffer, "%lu", frameTime);
      //printf("%s\n", buffer);
      SDL_SetWindowTitle(window.win, (const char*)buffer);
    }
  }

/*
  initRenderer(0);
  
  initIMG(IMG_INIT_PNG);
  initTTF();

  SDL_Texture *consenbren;
  SDL_Texture *fontTexture;
  SDL_Texture *banana;

  SDL_Event ev;

  TTF_Font *font;

  Mix_Chunk *keySound;

  mixerOpenAudio(22050, 2);

  keySound = mixerLoadAudio("src/bum.wav");

  consenbren = renderImageLoadTexture("src/img/con.png");
  banana = renderImageLoadTexture("src/img/banana.png");
  
  font = fontLoad("src/ttf/mononoki.ttf", 16);

  fontTexture = fontRenderLoadFont(font, "test", 255, 255, 255, 255);
 
  while(gameLoop)
  {
    // bug: as soon as one places 3 if statements, the function can only be triggered by pressing the desired key and a random key, maybe the user has to put the while(SDL_PollEvent...) loop
     into the main function, this method doesn't make sense, because it wouldn't be an engine anymore, I am probably doing something wrong
     play sound when key is pressed
    if(inputCheckKey(SDL_SCANCODE_C))
    {
      mixerPlayAudio(-1, keySound, 0);
    } 
    //------RENDER LOOP-----------

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

    // please use this method, as it is way more customizable
    // if input without delay is desired, make use of `` Uint8 *keys = SDL_GetKeyboardState(int numchar); ``
    while(SDL_PollEvent(&ev))
    {
      switch(ev.type)
      {
        case SDL_QUIT:
          gameLoop = false;
          break;

        case SDL_KEYDOWN:
          switch(ev.key.keysym.sym)
          {
            case SDLK_q:
              gameLoop = false;
              break;

            case SDLK_c:
              mixerPlayAudio(-1, keySound, 0);
            break;
          }
          break;
      }
    }
  }
  
  fontClose(font);

  mixerFreeChunk(keySound);

  initDestroyTexture(fontTexture);
  initDestroyTexture(consenbren);
  initDestroyTexture(banana);
  */
  initQuit();
  return 0;
}
