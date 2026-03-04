#version 450 core

uniform mat4x4 mvp_matrix;

layout (location = 0) in vec4 vPosition;

void main()
{
  gl_Position = mvp_matrix * vPosition;
}
