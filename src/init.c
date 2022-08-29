#include "init.h"

SDL_Window *win;
SDL_Renderer *rend;

// -1 means failed and 0 means success

int initEngine(Uint32 flags)
{
  // use 0 for fallback
  /* flags:
  SDL_INIT_TIMER: timer subsystem
  SDL_INIT_AUDIO: audio subsystem
  SDL_INIT_VIDEO: video subsystem; automatically initializes the events subsystem
  SDL_INIT_JOYSTICK: joystick subsystem; automatically initializes the events subsystem
  SDL_INIT_HAPTIC: haptic (force feedback) subsystem
  SDL_INIT_GAMECONTROLLER: controller subsystem; automatically initializes the joystick subsystem
  SDL_INIT_EVENTS: events subsystem
  SDL_INIT_EVERYTHING: all of the above subsystems (fallback)
  SDL_INIT_NOPARACHUTE: compatibility; this flag is ignored
  */

  // 0 = SDL_INIT_EVERYTHING
  if(flags == (Uint32)0) flags = SDL_INIT_EVERYTHING;

  // error handling
  if(SDL_Init(flags) != 0)
  {
    SDL_Log("Failed to initialize SDL: %s\n", SDL_GetError());
    return -1;
  }
  return 0;
}

int initWindow(int WIDTH, int HEIGHT, int posX, int posY, Uint32 flags)
{
  // use 0 for nothing (recommended)
  /* flags:
  --------------------------------------------------------------------------------
  SDL_WINDOW_FULLSCREEN: fullscreen window
  SDL_WINDOW_FULLSCREEN_DESKTOP: fullscreen window at desktop resolution
  SDL_WINDOW_OPENGL: window usable with an OpenGL context
  SDL_WINDOW_VULKAN: window usable with a Vulkan instance
  SDL_WINDOW_METAL: window usable with a Metal instance
  SDL_WINDOW_HIDDEN: window is not visible
  SDL_WINDOW_BORDERLESS: no window decoration
  SDL_WINDOW_RESIZABLE: window can be resized
  SDL_WINDOW_MINIMIZED: window is minimized
  SDL_WINDOW_MAXIMIZED: window is maximized
  SDL_WINDOW_INPUT_GRABBED: window has grabbed input focus
  SDL_WINDOW_ALLOW_HIGHDPI: window should be created in high-DPI mode if supported
  --------------------------------------------------------------------------------
*/
  // create window
  win = SDL_CreateWindow("", posX, posY, WIDTH, HEIGHT, flags);

  // error handling
  if(!win)
  {
    errorHandling("Failed to initialize the Window: ", 0);
    return -1;
  }
  return 0;
}

int initRenderer(Uint32 flags)
{
  // use 0 for fallback (recommended)
  /* flags:
  -------------------------------------------
  SDL_RENDER_PRESENTVSYNC:  present is synchronized with the refresh rate (fallback)
  SDL_RENDER_SOFTWARE:      the renderer is a software fallback
  SDL_RENDER_ACCELERATED:   the renderer uses hardware acceleration
  SDL_RENDER_TARGETTEXTURE: the renderer supports rendering to texture
  */
  
  // 0 == SDL_RENDERER_PRESENTVSYNC
  if(flags == 0) flags = SDL_RENDERER_PRESENTVSYNC;

  //create renderer
  rend = SDL_CreateRenderer(win, -1, flags);

  // error handling
  if(!rend) 
  {
    errorHandling("Failed to initialize the Renderer: ", 0);
    return -1;
  }
  return 0;
}

bool usingTTF = false;

int initTTF()
{
  // error handling
  if(TTF_Init() == -1)
  {
    errorHandling("Failed to initialize SDL_ttf: ", 3);
    return -1;
  }
  usingTTF = true;
  return 0;
}

bool usingIMG = false;

int initIMG(Uint32 flags)
{
  /* flags:
    _INIT_JPG 
    _INIT_PNG 
    _INIT_TIF 
    _INIT_WEBP
    _INIT_JXL 
    _INIT_AVIF 
  */

  if(IMG_Init(flags) == 0)
  {
    errorHandling("Failed Initializing SDL_image Library: ", 1); 
    return -1;
  }
  usingIMG = true;
  return 0;
}

bool usingMixer = false;

int initMixer(Uint32 flags)
{
  /* flags:
    MIX_INIT_FLAC 
    MIX_INIT_MOD
    MIX_INIT_MP3 
    MIX_INIT_OGG 
    MIX_INIT_MID 
    MIX_INIT_OPUS 
  */

  if(Mix_Init(flags) == 0) 
  {
    errorHandling("Failed to initialize SDL_mixer: ", 2);
    return -1;
  }
  usingMixer = true;
  return 0;
}

void initQuit()
{
  //don't forget to free memory with SDL_Destroy...
  SDL_DestroyRenderer(rend);
  SDL_DestroyWindow(win);
  // check initialized libraries
  if(usingTTF) TTF_Quit();
  if(usingIMG) IMG_Quit();
  if(usingMixer) Mix_Quit();

  SDL_Quit();
}

void initDestroyTexture(SDL_Texture *texture)
{
  SDL_DestroyTexture(texture);
}

void errorHandling(char *msg, int type)
{
  switch(type)
  {
    case 0:
      SDL_Log("%s%s\n", msg, SDL_GetError());
      break;
    case 1:
      SDL_Log("%s%s\n", msg, IMG_GetError());
      break;
    case 2:
      SDL_Log("%s%s\n", msg, Mix_GetError());
      break;
    case 3:
      SDL_Log("%s%s\n", msg, TTF_GetError());
      break;
    default:
      break;
  }
}
