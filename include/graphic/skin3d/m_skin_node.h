#ifndef _M_M_SKIN_NODE_H
#define _M_M_SKIN_NODE_H

//EXPEND HEADER -- DO NOT DELETE THIS LINE
#include <graphic/m_node.h>
#include <graphic/m_shader.h>
#include <graphic/m_texture.h>
#include "m_skin_join.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EXTEND_M_SKIN_NODE_FUNC(type, content) \
  EXTEND_M_NODE_FUNC(type, \
  /*EXPAND FUNCTION -- DO NOT DELETE IT*/ \
	void(*set_join)(void*, void*); \
	void(*set_shader)(void*, void*); \
	void(*set_texture)(void*, void*); \
  content \
  );

#define EXTEND_M_SKIN_NODE(type, func, content) \
  EXTEND_M_NODE(type, func, \
  /*EXPAND FIELD -- DO NOT DELETE IT*/ \
	GLuint vbo; \
	GLuint vao; \
	m_shader* shader; \
	m_texture* texture; \
	m_skin_join* join; \
	int vertices_count; \
  content \
  );

EXTEND_M_SKIN_NODE_FUNC(m_skin_node_func,);

EXTEND_M_SKIN_NODE(m_skin_node, m_skin_node_func,);

void m_skin_node_free(m_skin_node* arg);
void m_skin_node_init(m_skin_node* arg);
/*EXPAND DECLARE INTERFACE FUNCTION -- DO NOT DELETE IT*/
void m_skin_node_set_join(m_skin_node* arg_0, m_skin_join* arg_1);
void m_skin_node_draw(m_skin_node* arg_0);

void m_skin_node_set_shader(m_skin_node* arg_0, m_shader* arg_1);
void m_skin_node_set_texture(m_skin_node* arg_0, m_texture* arg_1);

#define INHERIT_M_SKIN_NODE_FUNC \
  INHERIT_M_NODE_FUNC, \
  /*EXPAND FUNCTION INTERFACE ASSIGMENT -- DO NOT DELETE IT*/ \
	.set_join = m_skin_node_set_join, \
	.draw = m_skin_node_draw, \
	.set_shader = m_skin_node_set_shader, \
	.set_texture = m_skin_node_set_texture, \
  .free = m_skin_node_free

m_skin_node* m_skin_node_new();

#ifdef __cplusplus
}
#endif

#endif
