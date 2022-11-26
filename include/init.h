#ifndef __INIT_H_
#define __INIT_H_

#include "../include/incs.h"

// the user can create as many windows as he wants
typedef struct BananaWindow
{
  int w;
  int h;
  SDL_Window *win;
  SDL_GLContext *con;
  Uint32 flags;
  char *title;
}BananaWindow;

int initEngine(Uint32 flags);
int initWindow(BananaWindow window);
//int initRenderer(Uint32 flags);

//int initTTF();
int initIMG(Uint32 flags);
int initMixer(Uint32 flags);

//void initDestroyTexture(SDL_Texture *texture);

void initQuit();

void errorHandling(char *msg, int type);
#endif
