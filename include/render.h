#ifndef __RENDER_H__
#define __RENDER_H__

#include "init.h"

typedef struct BananaObject 
{
  float x;
  float y;

  float w;
  float h;

  float r;
  float g;
  float b;

  unsigned int shader;
}BananaObject;

void allocateInformation(void);

void addToVertices(BananaObject *obj);

unsigned int generateShader(void);

void fillBuffer(void);

void useBuffer(void);

void addObject(BananaObject *obj);

#endif
