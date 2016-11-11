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

mat4 matrix4_inverse(mat4 matrix)
{
  mat4 inv;
  float det;

  inv[0].x =  matrix[1].y  * matrix[2].z * matrix[3].w -
              matrix[1].y  * matrix[2].w * matrix[3].z -
              matrix[2].y  * matrix[1].z  * matrix[3].w +
              matrix[2].y  * matrix[1].w  * matrix[3].z +
              matrix[3].y * matrix[1].z  * matrix[2].w -
              matrix[3].y * matrix[1].w  * matrix[2].z;

  inv[1].x = -matrix[1].x  * matrix[2].z * matrix[3].w +
              matrix[1].x  * matrix[2].w * matrix[3].z +
              matrix[2].x  * matrix[1].z  * matrix[3].w -
              matrix[2].x  * matrix[1].w  * matrix[3].z -
              matrix[3].x * matrix[1].z  * matrix[2].w +
              matrix[3].x * matrix[1].w  * matrix[2].z;

  inv[2].x =  matrix[1].x  * matrix[2].y * matrix[3].w -
              matrix[1].x  * matrix[2].w * matrix[3].y -
              matrix[2].x  * matrix[1].y * matrix[3].w +
              matrix[2].x  * matrix[1].w * matrix[3].y +
              matrix[3].x * matrix[1].y * matrix[2].w -
              matrix[3].x * matrix[1].w * matrix[2].y;

  inv[3].x =  -matrix[1].x  * matrix[2].y * matrix[3].z +
                matrix[1].x  * matrix[2].z * matrix[3].y +
                matrix[2].x  * matrix[1].y * matrix[3].z -
                matrix[2].x  * matrix[1].z * matrix[3].y -
                matrix[3].x * matrix[1].y * matrix[2].z +
                matrix[3].x * matrix[1].z * matrix[2].y;

  inv[0].y = -matrix[0].y  * matrix[2].z * matrix[3].w +
              matrix[0].y  * matrix[2].w * matrix[3].z +
              matrix[2].y  * matrix[0].z * matrix[3].w -
              matrix[2].y  * matrix[0].w * matrix[3].z -
              matrix[3].y * matrix[0].z * matrix[2].w +
              matrix[3].y * matrix[0].w * matrix[2].z;

  inv[1].y =  matrix[0].x  * matrix[2].z * matrix[3].w -
              matrix[0].x  * matrix[2].w * matrix[3].z -
              matrix[2].x  * matrix[0].z * matrix[3].w +
              matrix[2].x  * matrix[0].w * matrix[3].z +
              matrix[3].x * matrix[0].z * matrix[2].w -
              matrix[3].x * matrix[0].w * matrix[2].z;

  inv[2].y = -matrix[0].x  * matrix[2].y * matrix[3].w +
              matrix[0].x  * matrix[2].w * matrix[3].y +
              matrix[2].x  * matrix[0].y * matrix[3].w -
              matrix[2].x  * matrix[0].w * matrix[3].y -
              matrix[3].x * matrix[0].y * matrix[2].w +
              matrix[3].x * matrix[0].w * matrix[2].y;

  inv[3].y = matrix[0].x  * matrix[2].y * matrix[3].z -
              matrix[0].x  * matrix[2].z * matrix[3].y -
              matrix[2].x  * matrix[0].y * matrix[3].z +
              matrix[2].x  * matrix[0].z * matrix[3].y +
              matrix[3].x * matrix[0].y * matrix[2].z -
              matrix[3].x * matrix[0].z * matrix[2].y;

  inv[0].z =  matrix[0].y  * matrix[1].z * matrix[3].w -
              matrix[0].y  * matrix[1].w * matrix[3].z -
              matrix[1].y  * matrix[0].z * matrix[3].w +
              matrix[1].y  * matrix[0].w * matrix[3].z +
              matrix[3].y * matrix[0].z * matrix[1].w -
              matrix[3].y * matrix[0].w * matrix[1].z;

  inv[1].z = -matrix[0].x  * matrix[1].z * matrix[3].w +
              matrix[0].x  * matrix[1].w * matrix[3].z +
              matrix[1].x  * matrix[0].z * matrix[3].w -
              matrix[1].x  * matrix[0].w * matrix[3].z -
              matrix[3].x * matrix[0].z * matrix[1].w +
              matrix[3].x * matrix[0].w * matrix[1].z;

  inv[2].z = matrix[0].x  * matrix[1].y * matrix[3].w -
              matrix[0].x  * matrix[1].w * matrix[3].y -
              matrix[1].x  * matrix[0].y * matrix[3].w +
              matrix[1].x  * matrix[0].w * matrix[3].y +
              matrix[3].x * matrix[0].y * matrix[1].w -
              matrix[3].x * matrix[0].w * matrix[1].y;

  inv[3].z =  -matrix[0].x  * matrix[1].y * matrix[3].z +
                matrix[0].x  * matrix[1].z * matrix[3].y +
                matrix[1].x  * matrix[0].y * matrix[3].z -
                matrix[1].x  * matrix[0].z * matrix[3].y -
                matrix[3].x * matrix[0].y * matrix[1].z +
                matrix[3].x * matrix[0].z * matrix[1].y;

  inv[0].w = -matrix[0].y * matrix[1].z * matrix[2].w +
              matrix[0].y * matrix[1].w * matrix[2].z +
              matrix[1].y * matrix[0].z * matrix[2].w -
              matrix[1].y * matrix[0].w * matrix[2].z -
              matrix[2].y * matrix[0].z * matrix[1].w +
              matrix[2].y * matrix[0].w * matrix[1].z;

  inv[1].w =  matrix[0].x * matrix[1].z * matrix[2].w -
              matrix[0].x * matrix[1].w * matrix[2].z -
              matrix[1].x * matrix[0].z * matrix[2].w +
              matrix[1].x * matrix[0].w * matrix[2].z +
              matrix[2].x * matrix[0].z * matrix[1].w -
              matrix[2].x * matrix[0].w * matrix[1].z;

  inv[2].w =  -matrix[0].x * matrix[1].y * matrix[2].w +
                matrix[0].x * matrix[1].w * matrix[2].y +
                matrix[1].x * matrix[0].y * matrix[2].w -
                matrix[1].x * matrix[0].w * matrix[2].y -
                matrix[2].x * matrix[0].y * matrix[1].w +
                matrix[2].x * matrix[0].w * matrix[1].y;

  inv[3].w = matrix[0].x * matrix[1].y * matrix[2].z -
              matrix[0].x * matrix[1].z * matrix[2].y -
              matrix[1].x * matrix[0].y * matrix[2].z +
              matrix[1].x * matrix[0].z * matrix[2].y +
              matrix[2].x * matrix[0].y * matrix[1].z -
              matrix[2].x * matrix[0].z * matrix[1].y;

  det = matrix[0].x * inv[0].x + matrix[0].y * inv[1].x + matrix[0].z * inv[2].x + matrix[0].w * inv[3].x;

  det = clamp(det, 0.0000001, 999999.0);

  det = 1.0 / det;

  inv = inv * det;

  return inv;
}


mat4 matrix4_transpose(mat4 matrix)
{
  mat4 m = mat4(matrix[0].x, matrix[1].x, matrix[2].x, matrix[3].x,
                matrix[0].y, matrix[1].y, matrix[2].y, matrix[3].y,
                matrix[0].z, matrix[1].z, matrix[2].z, matrix[3].z,
                matrix[0].w, matrix[1].w, matrix[2].w, matrix[3].w);
  return m;
}

void main()
{
    mod = model[int(model_index)];

    Texcoord = texcoord;
    gl_Position = proj * view * mod * vec4(position, 1.0);
    //Normal = normal;
    Normal = mat3(matrix4_transpose(matrix4_inverse(mod))) * normal;
    FragPos = vec3(mod * vec4(position, 1.0));
}
