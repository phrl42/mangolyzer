#type vertex
#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in float aTexID;

out vec4 vertexColor;
out vec2 texCoords;
out float texID;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

void main()
{
  gl_Position = uModel * uView * uProjection * vec4(aPos.x, aPos.y, aPos.z, 1.0f);

  vertexColor = aColor;
  texCoords = aTexCoords;
  texID = aTexID;
}

#type fragment
#version 460 core

in vec2 texCoords;
in vec4 vertexColor;
in float texID;

out vec4 FragColor;

uniform sampler2D fTexture[32];

void main()
{
  if(int(texID) >= 0)
  {
    FragColor = texture(fTexture[int(texID)], texCoords) * vertexColor;
  }
  else
  {
    FragColor = vertexColor;
  }
}