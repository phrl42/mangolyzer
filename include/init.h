#ifndef __INIT_H_
#define __INIT_H_

#include "incs.h"

extern SDL_Window *win;
extern SDL_Renderer *rend;

int initEngine(Uint32 flags);
int initWindow(int WIDTH, int HEIGHT, int posX, int posY, Uint32 flags);
int initRenderer(Uint32 flags);

int initTTF();
int initIMG(Uint32 flags);
int initMixer(Uint32 flags);

void initDestroyTexture(SDL_Texture *texture);

void initQuit();

void errorHandling(char *msg, int type);
#endif
