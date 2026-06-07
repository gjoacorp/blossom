#version 450 core

layout (std140, binding = 0) uniform CameraMatrices 
{
    mat4 projection; 
    mat4 view;       
}; 

uniform mat4 model;

layout (location = 0) in vec4 vPosition;

void main()
{
  gl_Position = projection * view * model * vPosition;
}
