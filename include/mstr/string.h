#ifndef _M_STRING_H
#define _M_STRING_H

#include <base/ref.h>

#ifdef __cplusplus
extern "C" {
#endif

struct m_string
{
	REF_MACRO
	unsigned char*	content;
	long	length;
};

struct m_string* new_string();

void mstr_mstr(struct m_string* des, struct m_string* src);

void mstr_char(struct m_string* des, unsigned char* src);

#ifdef __cplusplus
}
#endif

#endif
