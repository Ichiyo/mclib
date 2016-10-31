#ifndef _M_STRING_H
#define _M_STRING_H

#include <base/ref.h>

#ifdef __cplusplus
extern "C" {
#endif

struct _m_string
{
	REF_MACRO
	char*	content;
	long	length;
	void(*cat_str)(struct _m_string*, struct _m_string*);
	void(*cat_char)(struct _m_string*, char* src);
};
typedef struct _m_string m_string;

m_string* new_string();

#ifdef __cplusplus
}
#endif

#endif
