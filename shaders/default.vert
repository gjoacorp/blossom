#version 450 core

uniform mat4x4 model;
uniform mat4x4 view;
uniform mat4x4 projection;

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec4 vColor;
layout (location = 2) in vec2 vTexCoordinate;

out vec4 outColor;
out vec2 TexCoordinate;

void main()
{
  gl_Position = projection * view * model * vPosition;
  outColor = vColor;
  TexCoordinate = vTexCoordinate;
}
