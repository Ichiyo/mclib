#ifndef _M_SHADER_H
#define _M_SHADER_H

#include <base/ref.h>
#include <graphic/graphic.h>

#ifdef __cplusplus
extern "C" {
#endif

EXTEND_REF_FUNC(g_shader_func,
  void(*use)(void*);
  int(*get_id)(void*);
);

EXTEND_REF(g_shader, g_shader_func,);

g_shader* shader_new(const char* vertex_source, const char* fragment_source);
g_shader* shader_new_from_file(const char* vertex_file, const char* fragment_file);

#ifdef __cplusplus
}
#endif

#endif
