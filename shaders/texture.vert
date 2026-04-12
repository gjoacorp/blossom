#version 450 core

uniform mat4x4 mvp_matrix;

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec2 vTexCoord;

out vec2 TexCoord;

void main()
{
  gl_Position = mvp_matrix * vPosition;
  TexCoord = vTexCoord;
}
