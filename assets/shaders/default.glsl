#type vertex
#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in int aTexID;

out vec4 vertexColor;
out vec2 texCoords;
flat out int texID;

void main()
{
  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);

  vertexColor = aColor;
  texCoords = aTexCoords;
  texID = aTexID;
}

#type fragment
#version 460 core

in vec2 texCoords;
in vec4 vertexColor;
flat in int texID;

out vec4 FragColor;

uniform sampler2D fTexture[32];

void main()
{
  if(texID >= 0)
  {
    FragColor = texture(fTexture[texID], texCoords) * vertexColor;
  }
  else
  {
    FragColor = vertexColor;
  }
}