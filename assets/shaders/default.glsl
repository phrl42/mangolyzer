#type vertex
#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoords;

out vec4 vertexColor;
out vec2 texCoords;

void main()
{
  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);

  vertexColor = aColor;
  texCoords = aTexCoords;
}

#type fragment
#version 460 core

in vec2 texCoords;
in vec4 vertexColor;

out vec4 FragColor;

void main()
{
  FragColor = vertexColor;
}