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

//DO NOT DELETE THIS LINE
//TEMPLATE [i]
//plf_in float joinIds_[i-1]
//plf_in float weights_[i-1]

#if USE_MODEL_INDEX != 0
plf_in float model_index;
#endif

#if NUMBER_JOIN_IDS >= 1
plf_in float joinIds_0;
plf_in float weights_0;
#endif

#if NUMBER_JOIN_IDS >= 2
plf_in float joinIds_1;
plf_in float weights_1;
#endif

#if NUMBER_JOIN_IDS >= 3
plf_in float joinIds_2;
plf_in float weights_2;
#endif

#if NUMBER_JOIN_IDS >= 4
plf_in float joinIds_3;
plf_in float weights_3;
#endif

#if NUMBER_JOIN_IDS >= 5
plf_in float joinIds_4;
plf_in float weights_4;
#endif

#if NUMBER_JOIN_IDS >= 6
plf_in float joinIds_5;
plf_in float weights_5;
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
    vec4 nor = vec4(normal, 1.0);
#else
    vec4 pos;
    vec4 nor;
#endif

#if NUMBER_JOIN_IDS >= 1
  pos = joins[int(joinIds_0)] * vec4(position, 1.0) * weights_0;
  nor = joins[int(joinIds_0)] * vec4(normal, 1.0) * weights_0;
#endif

#if NUMBER_JOIN_IDS >= 2
  pos = joins[int(joinIds_1)] * vec4(position, 1.0) * weights_1 + pos;
  nor = joins[int(joinIds_1)] * vec4(normal, 1.0) * weights_1 + nor;
#endif

#if NUMBER_JOIN_IDS >= 3
  pos = joins[int(joinIds_2)] * vec4(position, 1.0) * weights_2 + pos;
  nor = joins[int(joinIds_2)] * vec4(normal, 1.0) * weights_2 + nor;
#endif

#if NUMBER_JOIN_IDS >= 4
  pos = joins[int(joinIds_3)] * vec4(position, 1.0) * weights_3 + pos;
  nor = joins[int(joinIds_3)] * vec4(normal, 1.0) * weights_3 + nor;
#endif

#if NUMBER_JOIN_IDS >= 5
  pos = joins[int(joinIds_4)] * vec4(position, 1.0) * weights_4 + pos;
  nor = joins[int(joinIds_4)] * vec4(normal, 1.0) * weights_4 + nor;
#endif

#if NUMBER_JOIN_IDS >= 6
  pos = joins[int(joinIds_5)] * vec4(position, 1.0) * weights_5 + pos;
  nor = joins[int(joinIds_5)] * vec4(normal, 1.0) * weights_5 + nor;
#endif

#if NUMBER_JOIN_IDS >= 7
  pos = joins[int(joinIds_6)] * vec4(position, 1.0) * weights_6 + pos;
  nor = joins[int(joinIds_6)] * vec4(normal, 1.0) * weights_6 + nor;
#endif

#if NUMBER_JOIN_IDS >= 8
  pos = joins[int(joinIds_7)] * vec4(position, 1.0) * weights_7 + pos;
  nor = joins[int(joinIds_7)] * vec4(normal, 1.0) * weights_7 + nor;
#endif

    pos[3] = 1.0;
    Texcoord = texcoord;
    gl_Position = proj * view * mod * pos;
    Normal = mat3(matrix4_transpose(matrix4_inverse(mod))) * vec3(nor);
    FragPos = vec3(mod * pos);
}
