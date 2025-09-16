#version 450 core

out vec4 fColor;

in vec4 outColor;
in vec2 TexCoordinate;

uniform sampler2D outTexture;

void main() 
{
  fColor = texture(outTexture, TexCoordinate);
}
