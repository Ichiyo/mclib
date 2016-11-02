#ifndef _M_STRING_H
#define _M_STRING_H

#include <base/ref.h>

#ifdef __cplusplus
extern "C" {
#endif

EXTEND_REF_FUNC(m_string_func,
	void(*cat_str)(void*, void*);
	void(*cat_char)(void*, void*src);
);

EXTEND_REF(m_string, m_string_func,
	char*	content;
	long	length;
);

m_string* new_string();

#ifdef __cplusplus
}
#endif

#endif
