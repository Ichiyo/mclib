#version 150 core
in vec3 Color;
in vec2 Texcoord;
out vec4 outColor;
uniform sampler2D tex;
uniform sampler2D tex2;
uniform float blend;
uniform float time;

void main()
{
  vec4 c = vec4(Color, 1.0);
  outColor =  c * mix(texture(tex, Texcoord), texture(tex2, Texcoord), blend);
}
