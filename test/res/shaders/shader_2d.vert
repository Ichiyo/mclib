#version 100
#ifdef GL_ES
#define plf_in attribute
#define plf_out varying
#define plf_texture texture2D
#else
#define plf_in in
#define plf_out out
#define plf_texture texture
#endif

plf_in vec2 position;
plf_in vec2 texcoord;
plf_out vec2 Texcoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    Texcoord = texcoord;
    gl_Position = proj * view * model * vec4(position, 0.0, 1.0);
}
