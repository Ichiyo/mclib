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
    outColor = vec4(1.0,0.0,0.0,1.0);
}
