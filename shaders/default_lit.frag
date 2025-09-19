#version 450 core

layout (location = 0) out vec4 fColor;

in vec3 normal;
in vec4 fragPos;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main() 
{
  // ambient
  float ambientStrength = 0.1;
  vec3 ambient = ambientStrength * lightColor;

  // diffuse 
  vec3 norm = normalize(normal);
  vec4 lightDir = normalize(vec4(lightPos,1.0) - fragPos);
  float diff = max(dot(vec4(norm, 1.0), lightDir), 0.0);
  vec3 diffuse = diff * lightColor;

  vec3 result = (ambient + diffuse) * objectColor;
  fColor = vec4(result, 1.0);
}
