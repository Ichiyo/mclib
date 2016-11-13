#ifndef _M_M_NODE3D_H
#define _M_M_NODE3D_H

//EXPEND HEADER -- DO NOT DELETE THIS LINE
#include <graphic/graphic.h>
#include <graphic/m_node.h>
#include <graphic/m_texture.h>
#include <graphic/m_shader.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EXTEND_M_NODE3D_FUNC(type, content) \
  EXTEND_M_NODE_FUNC(type, \
  /*EXPAND FUNCTION -- DO NOT DELETE IT*/ \
	void(*set_shader)(); \
	void(*set_texture)(); \
	void(*set_model_obj)(); \
  content \
  );

#define EXTEND_M_NODE3D(type, func, content) \
  EXTEND_M_NODE(type, func, \
  /*EXPAND FIELD -- DO NOT DELETE IT*/ \
	GLuint vbo; \
	GLuint vao; \
	int count; \
	m_shader* shader; \
	m_texture* texture; \
  content \
  );

EXTEND_M_NODE3D_FUNC(m_node3d_func,);

EXTEND_M_NODE3D(m_node3d, m_node3d_func,);

void m_node3d_free(m_node3d* arg);
void m_node3d_init(m_node3d* arg);
/*EXPAND DECLARE INTERFACE FUNCTION -- DO NOT DELETE IT*/

void m_node3d_set_shader(m_node3d* arg_0, m_shader* arg_1);
void m_node3d_set_texture(m_node3d* arg_0, m_texture* arg_1);
void m_node3d_set_model_obj(m_node3d* arg_0, char* arg_1);
void m_node3d_draw(m_node3d* arg_0);

#define INHERIT_M_NODE3D_FUNC \
  INHERIT_M_NODE_FUNC, \
  /*EXPAND FUNCTION INTERFACE ASSIGMENT -- DO NOT DELETE IT*/ \
	.set_shader = m_node3d_set_shader, \
	.set_texture = m_node3d_set_texture, \
	.set_model_obj = m_node3d_set_model_obj, \
	.draw = m_node3d_draw, \
  .free = m_node3d_free

m_node3d* m_node3d_new();

#ifdef __cplusplus
}
#endif

#endif
