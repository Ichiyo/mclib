#ifndef _M_M_SPRITE2D_H
#define _M_M_SPRITE2D_H

//EXPEND HEADER -- DO NOT DELETE THIS LINE
#include <graphic/graphic.h>
#include <graphic/m_node.h>
#include <graphic/m_texture.h>
#include <graphic/m_shader.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EXTEND_M_SPRITE2D_FUNC(type, content) \
  EXTEND_M_NODE_FUNC(type, \
  /*EXPAND FUNCTION -- DO NOT DELETE IT*/ \
	void(*set_shader)(void*,void*); \
	void(*set_texture)(void*,void*); \
  content \
  );

#define EXTEND_M_SPRITE2D(type, func, content) \
  EXTEND_M_NODE(type, func, \
  /*EXPAND FIELD -- DO NOT DELETE IT*/ \
	GLuint vbo; \
	GLuint ebo; \
	GLuint vao; \
	m_shader* shader; \
	m_texture* texture; \
  content \
  );

EXTEND_M_SPRITE2D_FUNC(m_sprite2d_func,);

EXTEND_M_SPRITE2D(m_sprite2d, m_sprite2d_func,);

void m_sprite2d_free(m_sprite2d* arg);
void m_sprite2d_init(m_sprite2d* arg);
/*EXPAND DECLARE INTERFACE FUNCTION -- DO NOT DELETE IT*/
void m_sprite2d_visit(m_sprite2d* arg_0, m_matrix4 arg_1, int arg_2);
void m_sprite2d_draw(m_sprite2d* arg_0);

void m_sprite2d_set_shader(m_sprite2d* arg_0, m_shader* arg_1);
void m_sprite2d_set_texture(m_sprite2d* arg_0, m_texture* arg_1);

#define INHERIT_M_SPRITE2D_FUNC \
  INHERIT_M_NODE_FUNC, \
  /*EXPAND FUNCTION INTERFACE ASSIGMENT -- DO NOT DELETE IT*/ \
	.visit = m_sprite2d_visit, \
	.draw = m_sprite2d_draw, \
	.set_shader = m_sprite2d_set_shader, \
	.set_texture = m_sprite2d_set_texture, \
  .free = m_sprite2d_free

m_sprite2d* m_sprite2d_new();

#ifdef __cplusplus
}
#endif

#endif
