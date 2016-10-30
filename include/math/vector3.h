#ifndef _M_VECTOR3_H
#define _M_VECTOR3_H

#if defined(__ARM_NEON__)
#include <arm_neon.h>
#endif

#include <math/types.h>
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

static __inline__ vector3 vector3_new(float x, float y, float z);
static __inline__ vector3 vector3_neg(vector3 vector);
static __inline__ vector3 vector3_add(vector3 left, vector3 right);
static __inline__ vector3 vector3_sub(vector3 left, vector3 right);
static __inline__ vector3 vector3_mul(vector3 left, vector3 right);
static __inline__ vector3 vector3_div(vector3 left, vector3 right);
static __inline__ vector3 vector3_add_scalar(vector3 left, float scalar);
static __inline__ vector3 vector3_sub_scalar(vector3 left, float scalar);
static __inline__ vector3 vector3_mul_scalar(vector3 left, float scalar);
static __inline__ vector3 vector3_div_scalar(vector3 left, float scalar);
static __inline__ vector3 vector3_normalize(vector3 vector);
static __inline__ float   vector3_dot_product(vector3 left, vector3 right);
static __inline__ float   vector3_length(vector3 vector);
static __inline__ float   vector3_distance(vector3 left, vector3 right);
static __inline__ vector3 vector3_lerp(vector3 begin, vector3 end, float t);
static __inline__ vector3 vector3_cross_product(vector3 left, vector3 right);
static __inline__ vector3 vector3_project(vector3 vectorToProject, vector3 projectionVector);

static __inline__ vector3 vector3_new(float x, float y, float z)
{
  vector3 ret = {x, y, z};
  return ret;
}

static __inline__ vector3 vector3_neg(vector3 vector)
{
  vector3 ret = {-vector.v[0], -vector.v[1], -vector.v[2]};
  return ret;
}

static __inline__ vector3 vector3_add(vector3 left, vector3 right)
{
  vector3 ret = {
    left.v[0] + right.v[0],
    left.v[1] + right.v[1],
    left.v[2] + right.v[2]
  };
  return ret;
}

static __inline__ vector3 vector3_sub(vector3 left, vector3 right)
{
  vector3 ret = {
    left.v[0] - right.v[0],
    left.v[1] - right.v[1],
    left.v[2] - right.v[2]
  };
  return ret;
}

static __inline__ vector3 vector3_mul(vector3 left, vector3 right)
{
  vector3 ret = {
    left.v[0] * right.v[0],
    left.v[1] * right.v[1],
    left.v[2] * right.v[2]
  };
  return ret;
}

static __inline__ vector3 vector3_div(vector3 left, vector3 right)
{
  vector3 ret = {
    left.v[0] / right.v[0],
    left.v[1] / right.v[1],
    left.v[2] / right.v[2]
  };
  return ret;
}

static __inline__ vector3 vector3_add_scalar(vector3 left, float scalar)
{
  vector3 ret = {
    left.v[0] + scalar,
    left.v[1] + scalar,
    left.v[2] + scalar
  };
  return ret;
}

static __inline__ vector3 vector3_sub_scalar(vector3 left, float scalar)
{
  vector3 ret = {
    left.v[0] - scalar,
    left.v[1] - scalar,
    left.v[2] - scalar
  };
  return ret;
}

static __inline__ vector3 vector3_mul_scalar(vector3 left, float scalar)
{
  vector3 ret = {
    left.v[0] * scalar,
    left.v[1] * scalar,
    left.v[2] * scalar
  };
  return ret;
}

static __inline__ vector3 vector3_div_scalar(vector3 left, float scalar)
{
  vector3 ret = {
    left.v[0] / scalar,
    left.v[1] / scalar,
    left.v[2] / scalar
  };
  return ret;
}

static __inline__ vector3 vector3_normalize(vector3 vector)
{
  float scale = 1.0f / vector3_length(vector);
  vector3 v = vector3_mul_scalar(vector, scale);
  return v;
}

static __inline__ float   vector3_dot_product(vector3 left, vector3 right)
{
  return left.v[0] * right.v[0] + left.v[1] * right.v[1] + left.v[2] * right.v[2];
}

static __inline__ float   vector3_length(vector3 vector)
{
  return sqrt(vector.v[0] * vector.v[0] + vector.v[1] * vector.v[1] + vector.v[2] * vector.v[2]);
}

static __inline__ float   vector3_distance(vector3 left, vector3 right)
{
  return vector3_length(vector3_sub(right, left));
}

static __inline__ vector3 vector3_lerp(vector3 begin, vector3 end, float t)
{
  vector3 ret = {
    begin.v[0] + (end.v[0] - begin.v[0]) * t,
    begin.v[1] + (end.v[1] - begin.v[1]) * t,
    begin.v[2] + (end.v[2] - begin.v[2]) * t
  };
  return ret;
}

static __inline__ vector3 vector3_cross_product(vector3 left, vector3 right)
{
  vector3 v = { left.v[1] * right.v[2] - left.v[2] * right.v[1],
                left.v[2] * right.v[0] - left.v[0] * right.v[2],
                left.v[0] * right.v[1] - left.v[1] * right.v[0] };
  return v;
}

static __inline__ vector3 vector3_project(vector3 vectorToProject, vector3 projectionVector)
{
    float scale = vector3_dot_product(projectionVector, vectorToProject) / vector3_dot_product(projectionVector, projectionVector);
    vector3 v = vector3_mul_scalar(projectionVector, scale);
    return v;
}

#ifdef __cplusplus
}
#endif

#endif
