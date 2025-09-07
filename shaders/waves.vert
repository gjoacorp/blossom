#version 430

layout (location=0) in vec3 position;
uniform mat4 mv_matrix;
uniform mat4 proj_matrix;
uniform float time;

out vec4 varying_color;
out vec3 new_pos;

void main(void)
{ 
  float freq_a = 0.9f;
  float amp_a = 0.5f;
  float speed_a = 1.2f;
  float off_a = 0.0f;

  float freq_b = 0.2f;
  float amp_b = 0.9f;
  float speed_b = 0.3f;
  float off_b = 0.3f;

  float freq_c = 1.2f;
  float amp_c = 0.02f;
  float speed_c = 0.25f;
  float off_c = 0.7f;

  float wave_a = amp_a * sin((position.x + position.z) * freq_a + time * speed_a + off_a);
  float wave_b = amp_b * sin((position.x * position.y) * freq_b + time * speed_b + off_b);
  float wave_c = amp_c * cos((position.x * position.z) * freq_c + time * speed_c + off_c);

  vec3 new_pos = position + vec3(0.0f, wave_a + wave_b + wave_c, 0.0f);

  gl_Position = proj_matrix * mv_matrix * vec4(new_pos, 1.0);
  varying_color = normalize(vec4(new_pos, 1.0f));
}
