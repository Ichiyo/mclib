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

#define USE_MODEL_INDEX $use_model_index

#define NUMBER_JOIN_IDS $number_join_ids
#define NUMBER_JOINS $number_joins

plf_in vec3 position;
plf_in vec3 normal;
plf_in vec2 texcoord;

#if USE_MODEL_INDEX != 0
plf_in float model_index;
#endif

#if NUMBER_JOIN_IDS != 0
plf_in float joinIds[NUMBER_JOIN_IDS];
plf_in float weights[NUMBER_JOIN_IDS];
#endif

plf_out vec2 Texcoord;
plf_out vec3 Normal;
plf_out vec3 FragPos;

#if USE_MODEL_INDEX != 0
uniform mat4 model[128];
#else
uniform mat4 model;
#endif

uniform mat4 view;
uniform mat4 proj;

#if NUMBER_JOIN_IDS != 0
uniform mat4 joins[NUMBER_JOINS];
#endif

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
#if USE_MODEL_INDEX
    mod = model[int(model_index)];
#else
    mod = model;
#endif

#if NUMBER_JOIN_IDS == 0
    vec4 pos = vec4(position, 1.0);
    vec3 nor = normal;
#else
    vec4 pos;
    vec3 nor;
#endif

#if NUMBER_JOIN_IDS >= 1
  pos = joins[int(joinIds[0])] * vec4(position, 1.0) * weights[0];
  nor = joins[int(joinIds[0])] * vec4(normal, 1.0) * weights[0];
#endif

#if NUMBER_JOIN_IDS >= 2
  pos = joins[int(joinIds[1])] * vec4(position, 1.0) * weights[1] + pos;
  nor = joins[int(joinIds[1])] * vec4(normal, 1.0) * weights[1] + nor;
#endif

#if NUMBER_JOIN_IDS >= 3
  pos = joins[int(joinIds[2])] * vec4(position, 1.0) * weights[2] + pos;
  nor = joins[int(joinIds[2])] * vec4(normal, 1.0) * weights[2] + nor;
#endif

#if NUMBER_JOIN_IDS >= 4
  pos = joins[int(joinIds[3])] * vec4(position, 1.0) * weights[3] + pos;
  nor = joins[int(joinIds[3])] * vec4(normal, 1.0) * weights[3] + nor;
#endif

#if NUMBER_JOIN_IDS >= 5
  pos = joins[int(joinIds[4])] * vec4(position, 1.0) * weights[4] + pos;
  nor = joins[int(joinIds[4])] * vec4(normal, 1.0) * weights[4] + nor;
#endif

#if NUMBER_JOIN_IDS >= 6
  pos = joins[int(joinIds[5])] * vec4(position, 1.0) * weights[5] + pos;
  nor = joins[int(joinIds[5])] * vec4(normal, 1.0) * weights[5] + nor;
#endif

#if NUMBER_JOIN_IDS >= 7
  pos = joins[int(joinIds[6])] * vec4(position, 1.0) * weights[6] + pos;
  nor = joins[int(joinIds[6])] * vec4(normal, 1.0) * weights[6] + nor;
#endif

#if NUMBER_JOIN_IDS >= 8
  pos = joins[int(joinIds[7])] * vec4(position, 1.0) * weights[7] + pos;
  nor = joins[int(joinIds[7])] * vec4(normal, 1.0) * weights[7] + nor;
#endif

    pos[3] = 1.0;
    Texcoord = texcoord;
    gl_Position = proj * view * mod * pos;
    //Normal = normal;
    Normal = mat3(matrix4_transpose(matrix4_inverse(mod))) * nor;
    FragPos = vec3(mod * pos);
}
