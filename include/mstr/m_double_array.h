#ifndef _M_M_DOUBLE_ARRAY_H
#define _M_M_DOUBLE_ARRAY_H

//EXPEND HEADER -- DO NOT DELETE THIS LINE
#include <base/ref.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EXTEND_M_DOUBLE_ARRAY_FUNC(type, content) \
  EXTEND_REF_FUNC(type, \
  /*EXPAND FUNCTION -- DO NOT DELETE IT*/ \
	void(*push)(void*, double); \
	void(*remove)(void*, long); \
  content \
  );

#define EXTEND_M_DOUBLE_ARRAY(type, func, content) \
  EXTEND_REF(type, func, \
  /*EXPAND FIELD -- DO NOT DELETE IT*/ \
	double* data; \
	long length; \
  content \
  );

EXTEND_M_DOUBLE_ARRAY_FUNC(m_double_array_func,);

EXTEND_M_DOUBLE_ARRAY(m_double_array, m_double_array_func,);

void m_double_array_free(m_double_array* arg);
void m_double_array_init(m_double_array* arg);
/*EXPAND DECLARE INTERFACE FUNCTION -- DO NOT DELETE IT*/

void m_double_array_push(m_double_array* arg_0, double arg_1);
void m_double_array_remove(m_double_array* arg_0, long arg_1);

#define INHERIT_M_DOUBLE_ARRAY_FUNC \
  INHERIT_REF_FUNC, \
  /*EXPAND FUNCTION INTERFACE ASSIGMENT -- DO NOT DELETE IT*/ \
	.push = m_double_array_push, \
	.remove = m_double_array_remove, \
  .free = m_double_array_free

m_double_array* m_double_array_new();

#ifdef __cplusplus
}
#endif

#endif
