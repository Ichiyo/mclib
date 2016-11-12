#ifndef _M_STRING_H
#define _M_STRING_H

#include <base/ref.h>

#ifdef __cplusplus
extern "C" {
#endif

EXTEND_REF_FUNC(m_string_func, \
	void(*cat_str)(void*, void*); \
	void(*cat_char)(void*, void*src); \
	void(*replace_str)(void*, void* before, void* after); \
	void(*to_uppercase)(void*); \
	void(*to_lowercase)(void*); \
	void(*clear)(void*); \
	void(*insert_after)(); \
	int(*contain_char)(); \
	int(*contain_str)(); \
);

EXTEND_REF(m_string, m_string_func,
	char*	content;
	long	length;
);

m_string* new_string();
m_string* new_string_from_char(char* in);
m_string* new_string_from_str(m_string* in);

#ifdef __cplusplus
}
#endif

#endif
