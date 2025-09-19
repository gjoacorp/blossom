#version 450 core

uniform mat4x4 model;
uniform mat4x4 view;
uniform mat4x4 projection;

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec3 vNormal;

out vec4 fragPos;
out vec3 normal;

void main()
{
  fragPos = vec4(model * vPosition);
  normal = vNormal;

  gl_Position = projection * view * model * vPosition;
}
