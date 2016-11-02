#ifndef _M_STRING_H
#define _M_STRING_H

#include <base/ref.h>

#ifdef __cplusplus
extern "C" {
#endif

struct _m_string_func
{
	REF_FUNC_MACRO
	void(*cat_str)(void*, void*);
	void(*cat_char)(void*, void*src);
};
typedef struct _m_string_func m_string_func;

struct _m_string
{
	CONSTRUCT_REF(m_string_func)
	char*	content;
	long	length;
};
typedef struct _m_string m_string;

m_string* new_string();

#ifdef __cplusplus
}
#endif

#endif
