#ifndef _M_VECTOR4_H
#define _M_VECTOR4_H

#if defined(__ARM_NEON__)
#include <arm_neon.h>
#endif

#include <math/types.h>
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

static __inline__ vector4 vector4_new(float x, float y, float z, float w);
static __inline__ vector4 vector4_neg(vector4 vector);
static __inline__ vector4 vector4_add(vector4 left, vector4 right);
static __inline__ vector4 vector4_sub(vector4 left, vector4 right);
static __inline__ vector4 vector4_mul(vector4 left, vector4 right);
static __inline__ vector4 vector4_div(vector4 left, vector4 right);
static __inline__ vector4 vector4_add_scalar(vector4 left, float scalar);
static __inline__ vector4 vector4_sub_scalar(vector4 left, float scalar);
static __inline__ vector4 vector4_mul_scalar(vector4 left, float scalar);
static __inline__ vector4 vector4_div_scalar(vector4 left, float scalar);
static __inline__ vector4 vector4_normalize(vector4 vector);
static __inline__ float   vector4_dot_product(vector4 left, vector4 right);
static __inline__ float   vector4_length(vector4 vector);
static __inline__ float   vector4_distance(vector4 left, vector4 right);
static __inline__ vector4 vector4_lerp(vector4 begin, vector4 end, float t);
static __inline__ vector4 vector4_cross_product(vector4 left, vector4 right);
static __inline__ vector4 vector4_project(vector4 vectorToProject, vector4 projectionVector);

static __inline__ vector4 vector4_new(float x, float y, float z, float w)
{
  vector4 ret = {x, y, z, w};
  return ret;
}

static __inline__ vector4 vector4_neg(vector4 vector)
{
#if defined(__ARM_NEON__)
    float32x4_t v = vnegq_f32(*(float32x4_t *)&vector);
    return *(vector4 *)&v;
#else
    vector4 ret = { -vector.v[0], -vector.v[1], -vector.v[2], -vector.v[3] };
    return ret;
#endif
}

static __inline__ vector4 vector4_add(vector4 left, vector4 right)
{
#if defined(__ARM_NEON__)
    float32x4_t v = vaddq_f32(*(float32x4_t *)&left,
                              *(float32x4_t *)&right);
    return *(vector4 *)&v;
#else
    vector4 ret = {
      left.v[0] + right.v[0],
      left.v[1] + right.v[1],
      left.v[2] + right.v[2],
      left.v[3] + right.v[3] };
    return ret;
#endif
}

static __inline__ vector4 vector4_sub(vector4 left, vector4 right)
{
#if defined(__ARM_NEON__)
    float32x4_t v = vsubq_f32(*(float32x4_t *)&left,
                              *(float32x4_t *)&right);
    return *(vector4 *)&v;
#else
    vector4 ret = {
      left.v[0] - right.v[0],
      left.v[1] - right.v[1],
      left.v[2] - right.v[2],
      left.v[3] - right.v[3] };
    return ret;
#endif
}

static __inline__ vector4 vector4_mul(vector4 left, vector4 right)
{
#if defined(__ARM_NEON__)
    float32x4_t v = vmulq_f32(*(float32x4_t *)&left,
                              *(float32x4_t *)&right);
    return *(vector4 *)&v;
#else
    vector4 ret = {
      left.v[0] * right.v[0],
      left.v[1] * right.v[1],
      left.v[2] * right.v[2],
      left.v[3] * right.v[3] };
    return ret;
#endif
}

static __inline__ vector4 vector4_div(vector4 left, vector4 right)
{
#if defined(__ARM_NEON__)
  float32x4_t *vLeft = (float32x4_t *)&left;
  float32x4_t *vRight = (float32x4_t *)&right;
  float32x4_t estimate = vrecpeq_f32(*vRight);
  estimate = vmulq_f32(vrecpsq_f32(*vRight, estimate), estimate);
  estimate = vmulq_f32(vrecpsq_f32(*vRight, estimate), estimate);
  float32x4_t v = vmulq_f32(*vLeft, estimate);
  return *(vector4 *)&v;
#else
    vector4 ret = {
      left.v[0] / right.v[0],
      left.v[1] / right.v[1],
      left.v[2] / right.v[2],
      left.v[3] / right.v[3] };
    return ret;
#endif
}

static __inline__ vector4 vector4_add_scalar(vector4 left, float scalar)
{
#if defined(__ARM_NEON__)
    float32x4_t v = vaddq_f32(*(float32x4_t *)&left,
                              vdupq_n_f32((float32_t)scalar));
    return *(vector4 *)&v;
#else
    vector4 v = { left.v[0] + scalar,
                  left.v[1] + scalar,
                  left.v[2] + scalar,
                  left.v[3] + scalar};
    return v;
#endif
}

static __inline__ vector4 vector4_sub_scalar(vector4 left, float scalar)
{
  #if defined(__ARM_NEON__)
      float32x4_t v = vsubq_f32(*(float32x4_t *)&left,
                                vdupq_n_f32((float32_t)scalar));
      return *(vector4 *)&v;
  #else
      vector4 v = { left.v[0] - scalar,
                    left.v[1] - scalar,
                    left.v[2] - scalar,
                    left.v[3] - scalar};
      return v;
  #endif
}

static __inline__ vector4 vector4_mul_scalar(vector4 left, float scalar)
{
  #if defined(__ARM_NEON__)
      float32x4_t v = vmulq_f32(*(float32x4_t *)&left,
                                vdupq_n_f32((float32_t)scalar));
      return *(vector4 *)&v;
  #else
      vector4 v = { left.v[0] * scalar,
                    left.v[1] * scalar,
                    left.v[2] * scalar,
                    left.v[3] * scalar};
      return v;
  #endif
}

static __inline__ vector4 vector4_div_scalar(vector4 left, float scalar)
{
  #if defined(__ARM_NEON__)
      float32x4_t values = vdupq_n_f32((float32_t)scalar);
      float32x4_t estimate = vrecpeq_f32(values);
      estimate = vmulq_f32(vrecpsq_f32(values, estimate), estimate);
      estimate = vmulq_f32(vrecpsq_f32(values, estimate), estimate);
      float32x4_t v = vmulq_f32(*(float32x4_t *)&left, estimate);
      return *(vector4 *)&v;
  #else
      vector4 v = { left.v[0] / scalar,
                    left.v[1] / scalar,
                    left.v[2] / scalar,
                    left.v[3] / scalar };
      return v;
  #endif
}

static __inline__ vector4 vector4_normalize(vector4 vector)
{
  float scale = 1.0f / vector4_length(vector);
  vector4 v = vector4_mul_scalar(vector, scale);
  return v;
}

static __inline__ float   vector4_dot_product(vector4 left, vector4 right)
{
#if defined(__ARM_NEON__)
  float32x4_t v = vmulq_f32(*(float32x4_t *)&left,
                            *(float32x4_t *)&right);
  float32x2_t v2 = vpadd_f32(vget_low_f32(v), vget_high_f32(v));
  v2 = vpadd_f32(v2, v2);
  return vget_lane_f32(v2, 0);
#else
  return left.v[0] * right.v[0] + left.v[1] * right.v[1] + left.v[2] * right.v[2] + left.v[3] * right.v[3];
#endif
}

static __inline__ float   vector4_length(vector4 vector)
{
#if defined(__ARM_NEON__)
    float32x4_t v = vmulq_f32(*(float32x4_t *)&vector,
                              *(float32x4_t *)&vector);
    float32x2_t v2 = vpadd_f32(vget_low_f32(v), vget_high_f32(v));
    v2 = vpadd_f32(v2, v2);
    return sqrt(vget_lane_f32(v2, 0));
#else
    return sqrt(vector.v[0] * vector.v[0] +
                vector.v[1] * vector.v[1] +
                vector.v[2] * vector.v[2] +
                vector.v[3] * vector.v[3]);
#endif
}

static __inline__ float   vector4_distance(vector4 left, vector4 right)
{
  return vector4_length(vector4_sub(right, left));
}

static __inline__ vector4 vector4_lerp(vector4 begin, vector4 end, float t)
{
#if defined(__ARM_NEON__)
    float32x4_t vDiff = vsubq_f32(*(float32x4_t *)&end,
                                  *(float32x4_t *)&begin);
    vDiff = vmulq_f32(vDiff, vdupq_n_f32((float32_t)t));
    float32x4_t v = vaddq_f32(*(float32x4_t *)&begin, vDiff);
    return *(vector4 *)&v;
#else
    vector4 v = { begin.v[0] + ((end.v[0] - begin.v[0]) * t),
                  begin.v[1] + ((end.v[1] - begin.v[1]) * t),
                  begin.v[2] + ((end.v[2] - begin.v[2]) * t),
                  begin.v[3] + ((end.v[3] - begin.v[3]) * t) };
    return v;
#endif
}

static __inline__ vector4 vector4_cross_product(vector4 left, vector4 right)
{
  vector4 v = { left.v[1] * right.v[2] - left.v[2] * right.v[1],
                left.v[2] * right.v[0] - left.v[0] * right.v[2],
                left.v[0] * right.v[1] - left.v[1] * right.v[0],
                0.0f };
  return v;
}

static __inline__ vector4 vector4_project(vector4 vectorToProject, vector4 projectionVector)
{
    float scale = vector4_dot_product(projectionVector, vectorToProject) / vector4_dot_product(projectionVector, projectionVector);
    vector4 v = vector4_mul_scalar(projectionVector, scale);
    return v;
}

#ifdef __cplusplus
}
#endif

#endif
