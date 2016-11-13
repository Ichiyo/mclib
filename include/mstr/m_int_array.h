#ifndef _M_M_INT_ARRAY_H
#define _M_M_INT_ARRAY_H

//EXPEND HEADER -- DO NOT DELETE THIS LINE
#include <base/ref.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EXTEND_M_INT_ARRAY_FUNC(type, content) \
  EXTEND_REF_FUNC(type, \
  /*EXPAND FUNCTION -- DO NOT DELETE IT*/ \
	void(*push)(void*, int); \
	void(*remove)(void*, long); \
  content \
  );

#define EXTEND_M_INT_ARRAY(type, func, content) \
  EXTEND_REF(type, func, \
  /*EXPAND FIELD -- DO NOT DELETE IT*/ \
	int* data; \
	long length; \
  content \
  );

EXTEND_M_INT_ARRAY_FUNC(m_int_array_func,);

EXTEND_M_INT_ARRAY(m_int_array, m_int_array_func,);

void m_int_array_free(m_int_array* arg);
void m_int_array_init(m_int_array* arg);
/*EXPAND DECLARE INTERFACE FUNCTION -- DO NOT DELETE IT*/

void m_int_array_push(m_int_array* arg_0, int arg_1);
void m_int_array_remove(m_int_array* arg_0, long arg_1);

#define INHERIT_M_INT_ARRAY_FUNC \
  INHERIT_REF_FUNC, \
  /*EXPAND FUNCTION INTERFACE ASSIGMENT -- DO NOT DELETE IT*/ \
	.push = m_int_array_push, \
	.remove = m_int_array_remove, \
  .free = m_int_array_free

m_int_array* m_int_array_new();

#ifdef __cplusplus
}
#endif

#endif
