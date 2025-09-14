#version 430

layout (location=0) in vec3 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float time;

out vec4 varying_color;
out vec3 new_pos;

struct wave
{
  float frequency;
  float amplitude;
  float speed;
  float off_set;
  vec3 direction;
};

void main(void)
{ 
  wave wave_a = wave(0.9f, 0.50f, 1.20f, 0.0f, normalize(vec3(1.0f, 0.0f, 1.0f)));
  wave wave_b = wave(1.2f, 0.90f, 0.30f, 0.3f, normalize(vec3(1.0f, 0.0f, 0.0f)));
  wave wave_c = wave(0.75f, 0.42f, 0.25f, 0.7f, normalize(vec3(0.25f, 0.0f, -0.4f)));

  float wave_a_out = wave_a.amplitude * sin(dot(position, wave_a.direction) * wave_a.frequency + time * wave_a.speed + wave_a.off_set);
  float wave_b_out = wave_b.amplitude * sin(dot(position, wave_b.direction) * wave_b.frequency + time * wave_b.speed + wave_b.off_set);
  float wave_c_out = wave_c.amplitude * cos(dot(position, wave_c.direction) * wave_c.frequency + time * wave_c.speed + wave_c.off_set);

  vec3 new_pos = position + vec3(0.0f, wave_a_out + wave_b_out + wave_c_out, 0.0f);

  gl_Position = projection * view * model * vec4(new_pos, 1.0);
  varying_color = vec4(sin(5.0f * new_pos.y), cos(new_pos.y), sin(new_pos.y), 1.0);
}
