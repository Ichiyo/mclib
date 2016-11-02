#ifndef _M_DATA_H
#define _M_DATA_H

#include <base/ref.h>

#ifdef __cplusplus
extern "C" {
#endif

struct _m_data_func
{
  REF_FUNC_MACRO
  void(*put)(void*, char*, long);
};
typedef struct _m_data_func m_data_func;

struct _m_data
{
  CONSTRUCT_REF(m_data_func)
  char* bytes;
  long size;
};
typedef struct _m_data m_data;

m_data* data_new();

#ifdef __cplusplus
}
#endif

#endif
