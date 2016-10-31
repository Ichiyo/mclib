#include "mstr/string.h"
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

static void free_string(m_string* arg)
{
	free(arg->content);
	free(arg);
}

static void mstr_mstr(m_string* des, m_string* src)
{
	des->content = realloc(des->content, (des->length + src->length) * sizeof(char));
	memcpy(des->content + des->length, src->content, src->length);
	des->length = des->length + src->length;
}

static void mstr_char(m_string* des, char* src)
{
	unsigned long src_size = strlen(src);
	des->content = realloc(des->content, (des->length + src_size + 1) * sizeof(char));
	strncpy(des->content + des->length, src, src_size);
	des->length = des->length + src_size;
	des->content[des->length] = '\0';
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
m_string* new_string()
{
	REF_NEW_AUTO_RELEASE(m_string, str)
	mstr_char(str, "");
	str->free = free_string;
	str->cat_str = mstr_mstr;
	str->cat_char = mstr_char;
	return str;
}
#pragma GCC diagnostic pop

#ifdef __cplusplus
}
#endif
