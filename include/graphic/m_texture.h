#ifndef _M_M_TEXTURE_H
#define _M_M_TEXTURE_H

//EXPEND HEADER -- DO NOT DELETE THIS LINE
#include <base/ref.h>
#include <graphic/image.h>
#include <mstr/string.h>
#include <graphic/graphic.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EXTEND_M_TEXTURE_FUNC(type, content) \
  EXTEND_REF_FUNC(type, \
  /*EXPAND FUNCTION -- DO NOT DELETE IT*/ \
	void(*bind)(); \
	int(*get_width)(); \
	int(*get_height)(); \
  content \
  );

#define EXTEND_M_TEXTURE(type, func, content) \
  EXTEND_REF(type, func, \
  /*EXPAND FIELD -- DO NOT DELETE IT*/ \
	GLuint id; \
	int width; \
	int height; \
  content \
  );

EXTEND_M_TEXTURE_FUNC(m_texture_func,);

EXTEND_M_TEXTURE(m_texture, m_texture_func,);

void m_texture_free(m_texture* arg);
void m_texture_init(m_texture* arg);
/*EXPAND DECLARE INTERFACE FUNCTION -- DO NOT DELETE IT*/

void m_texture_bind(m_texture* arg_0, int arg_1);
int m_texture_get_width(m_texture* arg_0);
int m_texture_get_height(m_texture* arg_0);

#define INHERIT_M_TEXTURE_FUNC \
  INHERIT_REF_FUNC, \
  /*EXPAND FUNCTION INTERFACE ASSIGMENT -- DO NOT DELETE IT*/ \
	.bind = m_texture_bind, \
	.get_width = m_texture_get_width, \
	.get_height = m_texture_get_height, \
  .free = m_texture_free

m_texture* m_texture_new();
m_texture* m_texture_new_from_image(g_image*);
m_texture* m_texture_new_from_file_char(const char*);
m_texture* m_texture_new_from_file_string(m_string*);

void m_texture_free_cache();

#ifdef __cplusplus
}
#endif

#endif
