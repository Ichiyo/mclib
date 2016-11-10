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
plf_in vec3 position;
plf_in vec3 normal;
plf_in vec2 texcoord;
plf_in float model_index;
plf_out vec2 Texcoord;
plf_out vec3 Normal;
plf_out vec3 FragPos;
uniform mat4 model[128];
uniform mat4 view;
uniform mat4 proj;
mat4 mod;
void main()
{
    mod = model[int(model_index)];

    Texcoord = texcoord;
    gl_Position = proj * view * mod * vec4(position, 1.0);
    Normal = normal;
    //Normal = mat3(transpose(inverse(model[int(model_index)]))) * normal;
    FragPos = vec3(mod * vec4(position, 1.0));
}
