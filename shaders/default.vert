#version 450 core

uniform mat4x4 model;
uniform mat4x4 view;
uniform mat4x4 projection;

layout (location = 0) in vec4 vPosition;

void main()
{
  gl_Position = projection * view * model * vPosition;
}
