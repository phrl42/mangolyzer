#ifndef __RENDER_H__
#define __RENDER_H__

#include "init.h"

typedef struct BananaObject 
{
  float x;
  float y;

  float w;
  float h;
}BananaObject;

void adjustVertices(BananaObject *obj);

int generateShader(void);

void initBuffer(void);

void useBuffer(void);

void useObject(BananaObject *obj);

#endif
