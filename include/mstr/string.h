#ifndef _M_STRING_H
#define _M_STRING_H

#include <base/ref.h>

#ifdef __cplusplus
extern "C" {
#endif

struct _m_string
{
	REF_MACRO
	unsigned char*	content;
	long	length;
};
typedef struct _m_string m_string;

m_string* new_string();

void mstr_mstr(m_string* des, m_string* src);

void mstr_char(m_string* des, unsigned char* src);

#ifdef __cplusplus
}
#endif

#endif
