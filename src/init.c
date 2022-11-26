#include "../include/init.h"
//TODO: expand the limit with realloc..(if wanted)
// a maximum of 2 windows are allowed... more are just not needed for now (see above)..
SDL_Window *windowCollection[2];
SDL_GLContext *contextCollection[2];
int8_t posW = 0;// -1 means failed and 0 means success

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

  // set opengl version..
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
 
  // disallow older gl functions
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
}

int initWindow(BananaWindow window)
{
  // use 0 for an OpenGL Context (recommended)
  // the standard sdl renderer is not supported anymore..
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
  if(window.flags == (Uint32)0)
  {
    window.flags = SDL_WINDOW_OPENGL;
  }

  // create window
  window.win = SDL_CreateWindow(window.title, 0, 0, window.w, window.h, window.flags);

  // error handling
  if(!window.win)
  {
    errorHandling("Failed to initialize the Window: ", 0);
    return -1;
  }

  // create an opengl context on window creation...
  window.con = SDL_GL_CreateContext(window.win);
  if(!window.con)
  {
    errorHandling("Failed to create an OpenGL context: ", 0);
  }
  
  // add the created window to the collection
  windowCollection[posW] = window.win;
  
  // also add the opengl context
  contextCollection[posW] = window.con;
  posW++;
  return 0;
}
/*
int initRenderer(Uint32 flags)
{
  // use 0 for fallback (recommended)
  // flags:
  //-------------------------------------------
  //SDL_RENDER_PRESENTVSYNC:  present is synchronized with the refresh rate (fallback)
  //SDL_RENDER_SOFTWARE:      the renderer is a software fallback
  //SDL_RENDER_ACCELERATED:   the renderer uses hardware acceleration
  //SDL_RENDER_TARGETTEXTURE: the renderer supports rendering to texture
  
  
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
*/
/*bool usingTTF = false;

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
}*/

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
  //SDL_DestroyRenderer(rend);
  
  // delete every instance of sdl_window*
  while(posW < 0)
  {
    SDL_GL_DeleteContext(contextCollection[posW]);
    SDL_DestroyWindow(windowCollection[posW]);
    posW = posW - 1;
  }
  
  // check initialized libraries
  //if(usingTTF) TTF_Quit();
  if(usingIMG) IMG_Quit();
  if(usingMixer) Mix_Quit();

  // escape..
  SDL_Quit();
}

/*
void initDestroyTexture(SDL_Texture *texture)
{
  SDL_DestroyTexture(texture);
}
*/

// TODO: use enum
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
    /*case 3:
      SDL_Log("%s%s\n", msg, TTF_GetError());
      break;*/
    default:
      break;
  }
}
