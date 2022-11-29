#include "../include/init.h"
#include "../include/game.h" 

int main(int argc, char* argv[])
{
  // call the game initialization
  if(init() == -1) return -1;

  bool engine = true;
  
  SDL_Event ev;

  // fps calculation variables
  Uint64 lastTime = 0;
  float frameTime = lastTime;
  Uint64 beginTime = SDL_GetTicks64();
  char buffer[10];
  memset(buffer, '\0', sizeof(buffer) / sizeof(char));
  
  // set background color
  glClearColor(0.0, 0.0, 0.0, 0.0);
  while(engine)
  {
    // get starting time
    beginTime = SDL_GetTicks64();
    
    // clear buffer
    glClear(GL_COLOR_BUFFER_BIT);
    while(SDL_PollEvent(&ev))
    {
      if(ev.type == SDL_QUIT)
      {
        engine = false;
      }
    }
    // do game specific stuff here
    loop(frameTime);
    
    // reload the screen with the latest window
    SDL_GL_SwapWindow(getActiveWindow());

    // get elapsed time for frame
    lastTime = SDL_GetTicks64();
    printf("%f\n", frameTime); 

    // calculate the time of one frame
    frameTime = (lastTime - beginTime) / 60;
    if(frameTime <= 60)
    {
      sprintf(buffer, "%f", frameTime);
      //printf("%s\n", buffer);
      SDL_SetWindowTitle(getActiveWindow(), (const char*)buffer);
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
