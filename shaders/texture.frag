#version 450 core

layout (location = 0) out vec4 fColor;

in vec2 TexCoord;

uniform sampler2D Texture;

void main() 
{
  fColor = texture(Texture, TexCoord)+vec4(0.1, 0.0, 0.0, 1.0);
}
