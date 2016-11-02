#ifndef _M_DATA_H
#define _M_DATA_H

#include <base/ref.h>

#ifdef __cplusplus
extern "C" {
#endif

EXTEND_REF_FUNC(m_data_func,
  void(*put)(void*, char*, long);
);

EXTEND_REF(m_data, m_data_func,
  char* bytes;
  long size;
);

m_data* data_new();

#ifdef __cplusplus
}
#endif

#endif
