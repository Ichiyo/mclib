#ifndef _M_M_GENERIC_ARRAY_H
#define _M_M_GENERIC_ARRAY_H

//EXPEND HEADER -- DO NOT DELETE THIS LINE
#include <base/ref.h>
#include <string.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EXTEND_M_GENERIC_ARRAY_FUNC(type, content) \
  EXTEND_REF_FUNC(type, \
  /*EXPAND FUNCTION -- DO NOT DELETE IT*/ \
  content \
  );

#define EXTEND_M_GENERIC_ARRAY(type, func, content) \
  EXTEND_REF(type, func, \
  /*EXPAND FIELD -- DO NOT DELETE IT*/ \
	void* data; \
	long length; \
  content \
  );

EXTEND_M_GENERIC_ARRAY_FUNC(m_generic_array_func,);

EXTEND_M_GENERIC_ARRAY(m_generic_array, m_generic_array_func,);

void m_generic_array_free(m_generic_array* arg);
void m_generic_array_init(m_generic_array* arg);
/*EXPAND DECLARE INTERFACE FUNCTION -- DO NOT DELETE IT*/

#define GENERIC_ARRAY_PUSH(arr, type, val) \
  do { \
    arr->data = realloc(arr->data, (arr->length + 1) * sizeof(type)); \
    ((type*)arr->data)[arr->length] = val; \
    arr->length++; \
  } while(0)

#define GENERIC_ARRAY_REMOVE(arr, type, index) \
  do { \
    if(index >= 0 && index < arr->length) \
    { \
      if(index != arr->length - 1) memmove(arr->data+index, arr->data+index+1, (arr->length - index - 1) * sizeof(type)); \
      arr->length--; \
    } \
  } while(0)

#define GENERIC_ARRAY_GET(arr, type, index) (((type*)arr->data)[index])

#define INHERIT_M_GENERIC_ARRAY_FUNC \
  INHERIT_REF_FUNC, \
  /*EXPAND FUNCTION INTERFACE ASSIGMENT -- DO NOT DELETE IT*/ \
  .free = m_generic_array_free

m_generic_array* m_generic_array_new();

#ifdef __cplusplus
}
#endif

#endif
