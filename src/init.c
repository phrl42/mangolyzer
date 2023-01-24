#include "init.h"
//TODO: expand the limit with realloc..(if wanted)
// a maximum of 2 windows are allowed... more are just not needed for now (see above)..
SDL_Window *windowCollection[2];
// only use one context, because this is a simple engine
SDL_GLContext *context;
int8_t posW = -1;

// use the latest window by default
int8_t wantedPosW = 0;

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
    errorHandling("Failed to initialize SDL: ", 0);
    return -1;
  }
  return 0;

  // set opengl version..
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2); 
  // disallow older gl functions
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
}

int initBWindow(BananaWindow *window)
{
  ++posW;
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
  if(window->flags == (Uint32)0)
  {
    window->flags = SDL_WINDOW_OPENGL;
  }

  // create window
  // pass values
  // our window struct is a pointer, so go to the destination of our window struct, then take the value
  // for example width, which is not a pointer (just a value), take the value and return the address
  // where the window has been created, window.win is already a pointer, so just pass it
  window->win = SDL_CreateWindow(window->title, 0, 0, window->w, window->h, window->flags);

  // error handling
  if(!window->win)
  {
    errorHandling("Failed to initialize the Window: ", 0);
    return -1;
  }

  // create only one opengl context !!
  if(posW == 0)
  {
    // create an opengl context on the first window creation...
    context = SDL_GL_CreateContext(window->win);
    // check if it could create a context
    if(!context)
    {
      errorHandling("Failed to create an OpenGL context: ", 0);
      return -1;
    }
  }
  else // using an else is more efficient.. ):
  {
    //otherwise, activate the context for the next window created
    if(SDL_GL_MakeCurrent(window->win, context) < 0)
    {
      errorHandling("Failed to make the OpenGL context active", 0);
    }
  }
  

  // enable v-sync 
  if(SDL_GL_SetSwapInterval(1) == -1) 
  {
    errorHandling("Failed to enable v-sync: ", 0);
    return -1;
  }

  // add the created window to the collection
  windowCollection[posW] = window->win;
  
  return 0;
}

SDL_Window* getActiveWindow(void)
{
  // if 0 is used, take the latest window
  if(wantedPosW == 0)
  {
    // no need to make the context current
    return windowCollection[posW];
  }
  // if a different window is desired, make the context current, to render it
  if(SDL_GL_MakeCurrent(windowCollection[wantedPosW], context) < 0)
  {
    errorHandling("Failed to switch the desired window: ", 0);
  }
  // otherwise, just return the desired window
  return windowCollection[wantedPosW];
}

void setActiveWindow(int8_t wantpos)
{
  wantedPosW = wantpos;
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
/*
bool usingIMG = false;

int initIMG(Uint32 flags)
{
  // flags:
  //  _INIT_JPG 
  //  _INIT_PNG 
  //  _INIT_TIF 
  //  _INIT_WEBP
  //  _INIT_JXL 
  //  _INIT_AVIF 
  

  if(IMG_Init(flags) == 0)
  {
    errorHandling("Failed Initializing SDL_image Library: ", 1); 
    return -1;
  }
  usingIMG = true;
  return 0;
}*/

/*
bool usingMixer = false;

int initMixer(Uint32 flags)
{
  // flags:
  //  MIX_INIT_FLAC 
  //  MIX_INIT_MOD
  //  MIX_INIT_MP3 
  //  MIX_INIT_OGG 
  //  MIX_INIT_MID 
  //  MIX_INIT_OPUS 
  

  if(Mix_Init(flags) == 0) 
  {
    errorHandling("Failed to initialize SDL_mixer: ", 2);
    return -1;
  }
  usingMixer = true;
  return 0;
}*/

void initQuit(void)
{
  //don't forget to free memory with SDL_Destroy...
  //SDL_DestroyRenderer(rend);
  
  // delete every instance of sdl_window*
  while(posW < 0)
  {
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(windowCollection[posW]);
    posW = posW - 1;
  }
  
  // check initialized libraries
  //if(usingTTF) TTF_Quit();
  //if(usingIMG) IMG_Quit();
  //if(usingMixer) Mix_Quit();

  // escape..
  SDL_Quit();
}

/*
void initDestroyTexture(SDL_Texture *texture)
{
  SDL_DestroyTexture(texture);
}
*/

void errorHandling(char *msg, int type)
{
  switch(type)
  {
    case 0:
      SDL_Log("%s%s\n", msg, SDL_GetError());
      break;
    default:
      break;
  }
}
