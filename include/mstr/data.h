#ifndef _M_DATA_H
#define _M_DATA_H

#include <base/ref.h>

#ifdef __cplusplus
extern "C" {
#endif

struct _m_data
{
  REF_MACRO
  char* bytes;
  long size;
  void(*put)(struct _m_data*, char*, long);
};
typedef struct _m_data m_data;

m_data* data_new();

#ifdef __cplusplus
}
#endif

#endif
