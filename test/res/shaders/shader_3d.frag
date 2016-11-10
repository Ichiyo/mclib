#version 150 core
struct Material
{
    sampler2D diffuse;
    float shininess;
};

struct DirLight
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec2 Texcoord;
in vec3 Normal;
in vec3 FragPos;
out vec4 outColor;

uniform Material material;
uniform DirLight light;

void main()
{
  vec3 param = vec3(texture(material.diffuse, Texcoord));
  // Ambient
  vec3 ambient = light.ambient * param;

  // Diffuse
  vec3 norm = normalize(Normal);
  vec3 lightDir = normalize(-light.direction);
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = light.diffuse * diff * param;

  vec3 result = ambient + diffuse;

  outColor =  vec4(result, 1.0);
}
