#version 450 core

const int MAX_VERTICES = 20;

layout (points) in;
layout (line_strip, max_vertices = MAX_VERTICES) out;

struct branch
{
  vec4 left_leaf;
  vec4 right_leaf;
};

branch get_next_branch(vec4 point, int level)
{
  branch next_branch;
  vec4 delta = vec4(0.1 + (level * 0.025), 0.1 + (level * 0.025), 0.0, 0.0);

  next_branch.right_leaf = point + delta;
  next_branch.left_leaf  = point + vec4(-delta.x, delta.yzw);

  return next_branch;
}

void main() 
{    
  vec4 current_point = gl_in[0].gl_Position;
  gl_Position = current_point;
  EmitVertex();

  int levels = (MAX_VERTICES - 1) / 2;
  for (int level = 0; level < levels; ++level)
  {
    branch next_branch = get_next_branch(current_point, level);
    gl_Position = next_branch.left_leaf;
    EmitVertex();
    gl_Position = next_branch.right_leaf;
    EmitVertex();

    if (level % 2 == 0)
    {
      current_point = next_branch.left_leaf;
    }
    else
    {
      current_point = next_branch.right_leaf;
    }
  }
  EndPrimitive();
}
