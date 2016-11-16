#version 100

#ifdef GL_ES

precision mediump float;
#define plf_in varying
#define plf_out
#define plf_texture texture2D
#define plf_fragColor gl_FragColor

#else

#define plf_in in
#define plf_out out
#define plf_texture texture
out vec4 fragColor;
#define plf_fragColor fragColor

#endif

#define HAS_TEXTURE $has_texture

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

#if HAS_TEXTURE != 0
plf_in vec2 Texcoord;
#endif

plf_in vec3 Normal;
plf_in vec3 FragPos;

uniform Material material;
uniform DirLight light;

void main()
{
  #if HAS_TEXTURE != 0
  vec3 param = vec3(plf_texture(material.diffuse, Texcoord));
  #else
  vec3 param = vec3(1.0, 1.0, 1.0);
  #endif
  // Ambient
  vec3 ambient = light.ambient * param;

  // Diffuse
  vec3 norm = normalize(Normal);
  vec3 lightDir = normalize(-light.direction);
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = light.diffuse * diff * param;

  vec3 result = ambient + diffuse;

  plf_fragColor =  vec4(result, 1.0);
}
