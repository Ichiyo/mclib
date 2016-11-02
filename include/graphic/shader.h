#ifndef _M_SHADER_H
#define _M_SHADER_H

#include <base/ref.h>
#include <graphic/graphic.h>

#ifdef __cplusplus
extern "C" {
#endif

struct _g_shader_func
{
  REF_FUNC_MACRO
  void(*use)(void*);
};
typedef struct _g_shader_func g_shader_func;

struct _g_shader
{
  CONSTRUCT_REF(g_shader_func)
};
typedef struct _g_shader g_shader;

g_shader* shader_new(const char* vertex_source, const char* fragment_source);
g_shader* shader_new_from_file(const char* vertex_file, const char* fragment_file);

#ifdef __cplusplus
}
#endif

#endif
