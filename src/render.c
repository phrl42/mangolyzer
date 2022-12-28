#include "render.h"
#include "init.h"
#include "misc.h"
#define VSIZE 24

// opengl is a state machine

// this is the shader generating unit
const char* vertexShaderCon = 
                     "#version 330 core\n"
                     "layout (location = 0) in vec3 aPos;\n"
                     "layout (location = 1) in vec3 aColor;\n"
                     "out vec4 vertexColor;\n"
                     "void main()\n"
                     "{\n"
                     "  gl_Position = vec4(aPos, 1.0);\n"
                     "  vertexColor = vec4(aColor, 1.0);\n"
                     "}\0";

const char* fragmentShaderCon =
                     "#version 330 core\n"
                     "out vec4 FragColor;\n"
                     "in vec4 vertexColor; // we get the color from the vertex pipeline\n"
                     "void main()\n"
                     "{\n"
                     "  FragColor = vertexColor;\n"
                     "}\0";

struct renderInfo
{
  float *vertices;
  unsigned int offset;
}renderInfo;

struct renderInfo info;

void allocateInformation(void)
{
  info.offset = 0;
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
void addToVertices(BananaObject *obj)
{
  info.vertices = realloc(info.vertices, sizeof(float) * info.offset + sizeof(float) * VSIZE);

  // bottom left
  
  // COORDS
  info.vertices[info.offset + 0] = obj->x; // X 
  info.vertices[info.offset + 1] = obj->y - obj->h; // Y
  info.vertices[info.offset + 2] = 0.0f; // Z
  // COLORS
  info.vertices[info.offset + 3] = obj->r; // R
  info.vertices[info.offset + 4] = obj->g; // G
  info.vertices[info.offset + 5] = obj->b; // B
  
  // bottom right
  info.vertices[info.offset + 6] = obj->x + obj->w;
  info.vertices[info.offset + 7] = obj->y - obj->h;
  info.vertices[info.offset + 8] = 0.0f;
  
  info.vertices[info.offset + 9]  = obj->r;
  info.vertices[info.offset + 10] = obj->g;
  info.vertices[info.offset + 11] = obj->b;

  // top left (the actual placement)
  info.vertices[info.offset + 12] = obj->x;
  info.vertices[info.offset + 13] = obj->y;
  info.vertices[info.offset + 14] = 0.0f;
  
  info.vertices[info.offset + 15] = obj->r;
  info.vertices[info.offset + 16] = obj->g;
  info.vertices[info.offset + 17] = obj->b;

  // top right
  info.vertices[info.offset + 18] = obj->x + obj->w;
  info.vertices[info.offset + 19] = obj->y;
  info.vertices[info.offset + 20] = 0.0f;

  info.vertices[info.offset + 21] = obj->r;
  info.vertices[info.offset + 22] = obj->g;
  info.vertices[info.offset + 23] = obj->b;

  info.offset += VSIZE;
}

unsigned int shaderProgram = 0;
unsigned int generateShader(void)
{
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
   glGetShaderInfoLog(vertexShader, 512, NULL, log);
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
  }

  // the old shaders are not needed anymore 
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  
  return shaderProgram;
}

// vbo = a configuration of a vertex attribute structure ; the vbo itself is only the array
// vao = saves the whole vao configuration in a buffer, it also saves the ebo
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
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * info.offset, info.vertices, GL_STATIC_DRAW);
  
  // also use the ebo
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  // upload the indices array
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // linking the vertices array
  // telling opengl how our vertices array is built and how it should interpret the information
  // index location| size | type | normalization (not needed) | offset between attributes (one point)
  // | offset of the first attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),(void*)0);
  // enable vertex attribute (searching for vertices in the array, starting from 0)
  // make the connection between the vertices array and the vbo
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(sizeof(float) * 3));
  glEnableVertexAttribArray(1);

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

void useBuffer(void)
{
  // use the shader, from now on everything gets rendered with this shader (state machine)
  glUseProgram(shaderProgram);
  // use the vao preset
  glBindVertexArray(VAO);
  // draw the rectangle
  // one element = one index (from the indices)
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  //glDrawArrays(GL_TRIANGLES, 0, 3);
}

void addObject(BananaObject *obj)
{
  allocateInformation();
  addToVertices(obj);
  
  // we make use of render batching (merging draw calls -> only use one vertices array -> one shader)
  if(!shaderProgram)
  {
    obj->shader = generateShader();
  }
  else
  {
    obj->shader = shaderProgram;
  }
  fillBuffer();
}
