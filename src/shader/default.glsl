#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec4 vertexColor;

void main()
{
  vertexColor = vec4(aColor, 1.0);
  gl_Position = vec4(0, 0, 0, 1.0);
  //vertexTexCoords = aTexCoords;
}

#version 460 core

out vec4 FragColor;

in vec4 vertexColor;
// in vec2 vertexTexCoords;

//uniform sampler2D endTexture[8];

void main()
{
  FragColor = vertexColor;
}