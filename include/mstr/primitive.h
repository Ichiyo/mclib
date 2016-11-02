#ifndef _M_PRIMITIVE_H
#define _M_PRIMITIVE_H

#include <base/ref.h>

#ifdef __cplusplus
extern "C" {
#endif

EXTEND_REF(m_int, ref_func,
  long data;
);

m_int* new_int(long);

#ifdef __cplusplus
}
#endif

#endif
