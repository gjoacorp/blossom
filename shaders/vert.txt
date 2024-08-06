#version 430

layout (location=0) in vec3 position;
uniform mat4 mv_matrix;
uniform mat4 proj_matrix;
uniform float time;

out vec4 varying_color;
out vec3 new_pos;

void main(void)
{ 
   float freq_a = 2.0;
   float amp_a = 1.2f;
   float speed_a = 5.0f;
   float off_a = 0.0f;

   float wave_a = amp_a * sin((position.x + position.z) * freq_a + time * speed_a + off_a);

   vec3 new_pos = position + vec3(0.0, wave_a, 0.0);

   gl_Position = proj_matrix * mv_matrix * vec4(new_pos, 1.0);
   varying_color = normalize(vec4(position, 1.0)) + vec4(0.2, 0.2, 0.2, 0.2);
}
