#version 430

in vec4 varying_color;

out vec4 color;
uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

void main(void)
{ 
  color = varying_color;
}
