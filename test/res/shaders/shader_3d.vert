#version 150 core
in vec3 position;
in vec3 normal;
in vec2 texcoord;
in int model_index;
out vec2 Texcoord;
out vec3 Normal;
out vec3 FragPos;
uniform mat4 model[128];
uniform mat4 view;
uniform mat4 proj;

void main()
{
    Texcoord = texcoord;
    gl_Position = proj * view * model[model_index] * vec4(position, 1.0);
    //Normal = normal;
    Normal = mat3(transpose(inverse(model[model_index]))) * normal;
    FragPos = vec3(model[model_index] * vec4(position, 1.0));
}
