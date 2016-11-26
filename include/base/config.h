#ifndef _M_CONFIG_H
#define _M_CONFIG_H

#include <base/platform.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__clang__)

#define _f(T) ^T

#else //GNU

#define _f(T) *T

#endif

#ifdef __cplusplus
}
#endif

#endif
