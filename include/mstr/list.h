#ifndef _M_LIST_H
#define _M_LIST_H

#include <base/ref.h>

#ifdef __cplusplus
extern "C" {
#endif

EXTEND_REF_FUNC(m_list_func,
  void(*push)(struct _m_list*, void*, int);
  void(*pop)(struct _m_list*);
  void*(*get_last)(struct _m_list*);
  void*(*get_first)(struct _m_list*);
  void(*remove)(struct _m_list*, void*);
  void*(*get_index)(struct _m_list*, long);
);

EXTEND_REF(m_list, m_list_func,
  void* content;
  long size;
);

m_list* linked_list_new();
m_list* array_list_new();

#ifdef __cplusplus
}
#endif

#endif
