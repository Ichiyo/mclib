#ifndef _M_TEXTURE_H
#define _M_TEXTURE_H

#include <base/ref.h>
#include <graphic/image.h>
#include <mstr/string.h>

#ifdef __cplusplus
extern "C" {
#endif

EXTEND_REF_FUNC(g_texture_func,
  void(*bind)(void*,int);
  int(*get_width)(void*);
  int(*get_height)(void*);
);

EXTEND_REF(g_texture, g_texture_func,);

g_texture* texture_new_from_image(g_image*);
g_texture* texture_new_from_file_char(const char*);
g_texture* texture_new_from_file_string(m_string*);

void texture_free_cache();

#ifdef __cplusplus
}
#endif

#endif
