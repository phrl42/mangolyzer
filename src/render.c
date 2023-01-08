#include "render.h"
#include "init.h"
#include "misc.h"

#include "cglm/cglm.h"
#define VSIZE 32

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// opengl is a state machine

// this is the shader generating unit
const char* vertexShaderCon = 
                     "#version 330 core\n"
                     "layout (location = 0) in vec3 aPos;\n"
                     "layout (location = 1) in vec3 aColor;\n"
                     "layout (location = 2) in vec2 aTexCoords;\n"
                     "out vec4 vertexColor;\n"
                     "out vec2 vertexTexCoords;\n"
                     "uniform int useProj;\n"
                     "uniform mat4 model;\n"
                     "uniform mat4 view;\n"
                     "uniform mat4 projection;\n"
                     "void main()\n"
                     "{\n"
                     "  if(useProj == 1)\n"
                     "  {\n"
                     "    gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
                     "  }\n"
                     "  else\n"
                     "  {\n"
                     "    gl_Position = vec4(aPos, 1.0);\n"
                     "  }\n"
                     "  vertexColor = vec4(aColor, 1.0);\n"
                     "  vertexTexCoords = aTexCoords;\n"
                     "}\0";

const char* fragmentShaderCon =
                     "#version 330 core\n"
                     "out vec4 FragColor;\n"
                     "in vec4 vertexColor; // we get the color from the vertex pipeline\n"
                     "in vec2 vertexTexCoords;\n"
                     "uniform int vertexTexID;\n"
                     "uniform sampler2D endTexture;\n"
                     "void main()\n"
                     "{\n"
                     "  if(vertexTexID == 0)\n"
                     "  {\n"
                     "    FragColor = vertexColor;\n"
                     "  }\n"
                     "  else\n"
                     "  {\n"
                     "    FragColor = texture(endTexture, vertexTexCoords); // display texture\n"
                     "  }\n"
                     "}\0";

struct renderInfo
{
  unsigned int *shaderPrograms;
  unsigned int countShader;
  unsigned int latestShader;
  
  float *vertices;
  unsigned int offset;
  
  unsigned int *textures;
  unsigned int countTexture;
  unsigned int latestTexture;
  mat4 projection;
  mat4 view;
}renderInfo;

struct renderInfo info;

void allocateInformation(void)
{
  info.projection = GLM_MAT4_IDENTITY_INIT;
  info.view = GLM_MAT4_IDENTITY_INIT;

  info.offset = 0;
  info.countShader = 0;
  info.countTexture = 0;
}
void freeInformation(void)
{
  free(info.vertices);
  free(info.shaderPrograms);
  free(info.textures);
}

// vertices array (points) normalized after NDC, can be changed with glViewport
// vertex = point ; vertices = points
/*float vertices[] =
{
 //   X      Y      Z 
    0.5f,  -0.5f,  0.0f, // bottom left
   -0.5f,  -0.5f,  0.0f, // bottom right
   -0.5f,   0.5f,  0.0f, // top left
    0.5f,   0.5f,  0.0f  // top right
};*/
//float *vertices = malloc(sizeof(float) * 12);
// the indices array is used by the ebo and can simplify the drawing of a rectangle
// as it specifies the vertices of triangles that can be created
// 3 points = 1 triangle
unsigned int indices[] = 
{
  0, 1, 2, // first triangle
  1, 2, 3, // second triangle
};
void addToShader(float x, float y, float w, float h, float r, float g, float b, unsigned int textureID, enum Projection proj)
{
  info.vertices = realloc(info.vertices, sizeof(float) * info.offset + sizeof(float) * VSIZE);

  // bottom left
  
  // COORDS
  info.vertices[info.offset + 0] = x; // X 
  info.vertices[info.offset + 1] = y - h; // Y
  info.vertices[info.offset + 2] = 0.0f; // Z
  // COLORS
  info.vertices[info.offset + 3] = r; // R
  info.vertices[info.offset + 4] = g; // G
  info.vertices[info.offset + 5] = b; // B
  
  // TEXCOORDS
  info.vertices[info.offset + 6] = 0; // TX
  info.vertices[info.offset + 7] = 0; // TY

  // bottom right
  info.vertices[info.offset + 8] = x + w;
  info.vertices[info.offset + 9] = y - h;
  info.vertices[info.offset + 10] = 0.0f;
  
  info.vertices[info.offset + 11] = r;
  info.vertices[info.offset + 12] = g;
  info.vertices[info.offset + 13] = b;

  info.vertices[info.offset + 14] = 1;
  info.vertices[info.offset + 15] = 0;

  // top left (the actual placement)
  info.vertices[info.offset + 16] = x;
  info.vertices[info.offset + 17] = y;
  info.vertices[info.offset + 18] = 0.0f;
  
  info.vertices[info.offset + 19] = r;
  info.vertices[info.offset + 20] = g;
  info.vertices[info.offset + 21] = b;

  info.vertices[info.offset + 22] = 0;
  info.vertices[info.offset + 23] = 1;

  // top right
  info.vertices[info.offset + 24] = x + w;
  info.vertices[info.offset + 25] = y;
  info.vertices[info.offset + 26] = 0.0f;

  info.vertices[info.offset + 27] = r;
  info.vertices[info.offset + 28] = g;
  info.vertices[info.offset + 29] = b;

  info.vertices[info.offset + 30] = 1;
  info.vertices[info.offset + 31] = 1;

  info.offset += VSIZE;

  // add texture id to uniform
  glUseProgram(info.latestShader);
  glUniform1i(glGetUniformLocation(info.latestShader, "vertexTexID"), (int)textureID);

  // add mvp to shader and upload it
  // coordinate system (projection -> far objects become small and vice versa)
  
  // PERSPECTIVE

  // upload perspective
  // if projection is desired, enable the mvp logic
  if(proj == PERSPECTIVE)
  {
    glm_perspective(glm_rad(100.0f), (float)w / (float)h, 0.1f, 100.0f, info.projection);
    glUniform1i(glGetUniformLocation(info.latestShader, "useProj"), 1);
    glUniformMatrix4fv(glGetUniformLocation(info.latestShader, "projection"), 1, GL_FALSE, (float*)info.projection);
  }
  else 
  {
    glUniform1i(glGetUniformLocation(info.latestShader, "useProj"), 0);
  }
  // MODEL
  
  // model matrix (will be useful for having multiple textures and scaling them)
  mat4 model = GLM_MAT4_IDENTITY_INIT;
  // world coordinates
  glm_translate(model, (vec3){obj->x, obj->y, 0.0f});
  glUniformMatrix4fv(glGetUniformLocation(info.latestShader, "model"), 1, GL_FALSE, (float*)model);
  
  // VIEW

  // these are the camera coordinates
  glm_translate(info.view, (vec3){0.0f, 0.0f, -3.0f});
  glUniformMatrix4fv(glGetUniformLocation(info.latestShader, "view"), 1, GL_FALSE, (float*)info.view);
}

void adjustModelMatrix(mat4 model, vec3 coords)
{
  glm_translate(model, coords);
  glUniformMatrix4fv(glGetUniformLocation(info.latestShader, "model"), 1, GL_FALSE, (float*)model);
}

void adjustViewMatrix(mat4 view, vec3 coords)
{
  glm_translate(view, coords);
  info.view = view;
  glUniformMatrix4fv(glGetUniformLocation(info.latestShader, "view"), 1, GL_FALSE, (float*)info.view);
}

int generateShader(void)
{
  unsigned int shaderProgram;
  unsigned int vertexShader; // identifier for the vertexShader (there is only one)
  unsigned int fragmentShader; // identifier for the fragmentShader (there is only one)
  
  int success;
  char log[512];

  // prepare to compile the shader
  // create a shader place and save it's reference to vertexShader
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  // get the shader source code and upload it to the vertexShader place
  glShaderSource(vertexShader, 1, &vertexShaderCon, NULL);
  
  // compile shader
  glCompileShader(vertexShader);
  
  // error handling
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if(!success)
  {
    glGetShaderInfoLog(vertexShader, 512, NULL, log);
    Log(log, Error);
    return -1;
  } 
  
  // repeat the process with the fragment shader
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderCon, NULL);
  glCompileShader(fragmentShader);
  
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if(!success)
  {
   glGetShaderInfoLog(fragmentShader, 512, NULL, log);
   Log(log, Error);
   return -1;
  }
  Log("Compiled shader", Info);
  
  // link the shaders

  // create a shader program, which can be referenced later
  shaderProgram = glCreateProgram();
  
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  // error handling
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if(!success)
  {
    glGetProgramInfoLog(shaderProgram, 512, NULL, log);
    Log(log, Error);
    return -1;
  }

  // the old shaders are not needed anymore 
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
 
  // allocate space for a new shader
  info.shaderPrograms = realloc(info.shaderPrograms, sizeof(unsigned int) * info.countShader + sizeof(unsigned int)); 
  
  // save shader ids in array
  info.shaderPrograms[info.countShader] = shaderProgram;
  info.latestShader = shaderProgram;

  info.countShader += 1;
  return 0;
}

// vbo = a configuration of a vertex attribute structure ; the vbo itself is only the array
// vao = saves the whole vao configuration in a buffer, it also saves the ebo
// we only use one vao (there is only one norm)
unsigned int VAO; // "configuration saver" identifier
// one vao has to be used, because opengl requires it
void fillBuffer(void)
{
  unsigned int VBO; // vertex array identifier
  unsigned int EBO; // element buffer object identifier  
  
  // generate space for the vertex array object
  glGenVertexArrays(1, &VAO);
  // generate space for one vertex array
  glGenBuffers(1, &VBO);
  // also generate the ebo
  glGenBuffers(1, &EBO);

  // use the vao and save the following into it
  glBindVertexArray(VAO);

  
  // use the newly generated uffer
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // give the gpu our vertices array
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * info.offset, info.vertices, GL_DYNAMIC_DRAW);
  
  // also use the ebo
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  // upload the indices array
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

  // linking the vertices array
  // telling opengl how our vertices array is built and how it should interpret the information
  // index location | size (how many attributes) | type | normalization (not needed) | offset between attributes (one point)
  // | offset of the first attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),(void*)0);
  // enable vertex attribute (searching for vertices in the array, starting from 0)
  // make the connection between the vertices array and the vbo
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 3));
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(sizeof(float) * 6));
  glEnableVertexAttribArray(2);

  // unbind the vbo
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // do not unbind the ebo

  // unbind the vao

  glBindVertexArray(0);
  // use the vao preset
  //glBindVertexArray(VAO);
  // use the shader, from now on everything gets rendered with this shader (state machine)
  //glUseProgram(shaderProgram);
}

int loadTexture(BananaTexture *obj)
{
  // opengl enables the use of 16 textures simultaneously 
  // you can have more textures though
  // generate 1 texture
  unsigned int texture;
  glGenTextures(1, &texture);
  // use the newly generated texture
  glBindTexture(GL_TEXTURE_2D, texture);
  // adjust settings of the texture
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
 
  // load and save texture
  // flip the picture on the y-axis
  stbi_set_flip_vertically_on_load(true);

  obj->data = stbi_load(obj->path, &obj->w, &obj->h, &obj->channels, 0);
  if(!obj->data)
  {
    Log("Could not load texture", Error);
    texture = 0;
    return -1;
  }
  // load image into gpu
  
  if(obj->channels == 4)
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, obj->w, obj->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, obj->data);
  }
  else
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, obj->w, obj->h, 0, GL_RGB, GL_UNSIGNED_BYTE, obj->data);
  }
  glGenerateMipmap(GL_TEXTURE_2D);
  
  info.textures = realloc(info.textures, sizeof(unsigned int) * info.countTexture + sizeof(unsigned int));
  info.textures[info.countTexture] = texture;
  info.latestTexture = texture;

  obj->textureID = texture;
  info.countTexture += 1;
  
  stbi_image_free(obj->data);
 
  // unbind the texture
  glBindTexture(GL_TEXTURE_2D, 0);
  return 0; 
}

void useBuffer(void)
{
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, info.latestTexture);
  // use the shader, from now on everything gets rendered with this shader (state machine)
  glUseProgram(info.latestShader);
  // use the vao preset
  glBindVertexArray(VAO);
  // draw the rectangle
  // one element = one index (from the indices)
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  //glDrawArrays(GL_TRIANGLES, 0, 3);
}

void addRectangle(BananaRectangle *obj)
{
  addToShader(obj->x, obj->y, obj->w, obj->h, obj->r, obj->g, obj->b, 0, obj->proj);
  // we make use of render batching (merging draw calls -> only use one vertices array -> one shader)
  fillBuffer();
}

void addTexture(BananaTexture *obj)
{
  // initialize struct model
  obj->model = GLM_MAT4_IDENTITY_INIT;

  int w = obj->w;
  int h = obj->h;
  loadTexture(obj);
  addToShader(obj->x, obj->y, w, h, 0.0f, 0.0f, 0.0f, obj->textureID, obj->proj);
  fillBuffer();
}
