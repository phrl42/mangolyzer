#ifndef __RENDER_H__
#define __RENDER_H__

#include "init.h"

enum Projection = {NONE, PERSPECTIVE};

typedef struct BananaRectangle 
{
  float x;
  float y;

  float w;
  float h;

  float r;
  float g;
  float b;
}BananaRectangle;

typedef struct BananaTexture
{
  float x;
  float y;

  int w;
  int h;

  enum Projection proj;
  const char* path;
  unsigned char* data;

  int channels;
  unsigned int textureID;
}BananaTexture;

void allocateInformation(void);
void freeInformation(void);

void addToShader(float x, float y, float w, float h, float r, float g, float b, unsigned int textureID, enum Projection proj);

int generateShader(void);

void fillBuffer(void);

int loadTexture(BananaTexture *obj);

void useBuffer(void);

void addRectangle(BananaRectangle *obj);

void addTexture(BananaTexture *obj);

#endif
