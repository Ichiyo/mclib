#version 150 core
in vec3 position;
in vec3 normal;
in vec2 texcoord;
in int model_index;
out vec2 Texcoord;
out vec3 Normal;
out vec3 FragPos;
uniform mat4 model[512];
uniform mat4 view;
uniform mat4 proj;

void main()
{
    mat4 mod = model[model_index];
    Texcoord = texcoord;
    gl_Position = proj * view * mod * vec4(position, 1.0);
    //Normal = normal;
    Normal = mat3(transpose(inverse(mod))) * normal;
    FragPos = vec3(mod * vec4(position, 1.0));
}
