#ifndef _M_M_SHADER_H
#define _M_M_SHADER_H

//EXPEND HEADER -- DO NOT DELETE THIS LINE
#include <base/ref.h>
#include <graphic/graphic.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EXTEND_M_SHADER_FUNC(type, content) \
  EXTEND_REF_FUNC(type, \
  /*EXPAND FUNCTION -- DO NOT DELETE IT*/ \
	void(*use)(); \
	int(*get_id)(); \
  content \
  );

#define EXTEND_M_SHADER(type, func, content) \
  EXTEND_REF(type, func, \
  /*EXPAND FIELD -- DO NOT DELETE IT*/ \
	GLuint id; \
  content \
  );

EXTEND_M_SHADER_FUNC(m_shader_func,);

EXTEND_M_SHADER(m_shader, m_shader_func,);

void m_shader_free(m_shader* arg);
void m_shader_init(m_shader* arg);
/*EXPAND DECLARE INTERFACE FUNCTION -- DO NOT DELETE IT*/

void m_shader_use(m_shader* arg_0);
int m_shader_get_id(m_shader* arg_0);

#define INHERIT_M_SHADER_FUNC \
  INHERIT_REF_FUNC, \
  /*EXPAND FUNCTION INTERFACE ASSIGMENT -- DO NOT DELETE IT*/ \
	.use = m_shader_use, \
	.get_id = m_shader_get_id, \
  .free = m_shader_free

m_shader* m_shader_new();
m_shader* m_shader_new_from_source(const char* vertex_source, const char* fragment_source);
m_shader* m_shader_new_from_file(const char* vertex_file, const char* fragment_file);

#ifdef __cplusplus
}
#endif

#endif
