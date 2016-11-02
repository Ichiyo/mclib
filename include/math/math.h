#ifndef _M_MATH_H
#define _M_MATH_H

#include <math/types.h>
#include <math/vector2.h>
#include <math/vector3.h>
#include <math/vector4.h>
#include <math/matrix3.h>
#include <math/matrix4.h>
#include <math/quaternion.h>
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define DEG_TO_RAD(X) (X * M_PI / 180)
#define RAD_TO_DEG(X) (X * 180 / M_PI)

#ifdef __cplusplus
}
#endif

#endif
