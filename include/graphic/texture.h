#ifndef _M_TEXTURE_H
#define _M_TEXTURE_H

#include <base/ref.h>
#include <graphic/image.h>
#include <mstr/string.h>

#ifdef __cplusplus
extern "C" {
#endif

struct _g_texture
{
  REF_MACRO
  void(*bind)(void*,int);
};
typedef struct _g_texture g_texture;

g_texture* texture_new_from_image(g_image*);
g_texture* texture_new_from_file_char(const char*);
g_texture* texture_new_from_file_string(m_string*);

void texture_free_cache();

#ifdef __cplusplus
}
#endif

#endif
