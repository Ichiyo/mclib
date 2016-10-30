#include "mstr/string.h"
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

static void free_string(struct m_string* arg)
{
	free(arg->content);
	free(arg);
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
struct m_string* new_string()
{
	struct m_string* str = calloc(1, sizeof(struct m_string));
	mstr_char(str, "");
	ref_init(str);
	str->auto_release(str);
	str->free = free_string;
	return str;
}
#pragma GCC diagnostic pop

void mstr_mstr(struct m_string* des, struct m_string* src)
{
	des->content = realloc(des->content, (des->length + src->length) * sizeof(unsigned char));
	memcpy(des->content + des->length, src->content, src->length);
	des->length = des->length + src->length;
}

void mstr_char(struct m_string* des, unsigned char* src)
{
	unsigned long src_size = strlen(src);
	des->content = realloc(des->content, (des->length + src_size + 1) * sizeof(unsigned char));
	strncpy(des->content + des->length, src, src_size);
	des->length = des->length + src_size;
	des->content[des->length] = '\0';
}

#ifdef __cplusplus
}
#endif
