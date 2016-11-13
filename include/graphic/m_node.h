#ifndef _M_M_NODE_H
#define _M_M_NODE_H

//EXPEND HEADER -- DO NOT DELETE THIS LINE
#include <math/math.h>
#include <base/ref.h>
#include <mstr/list.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EXTEND_M_NODE_FUNC(type, content) \
  EXTEND_REF_FUNC(type, \
  /*EXPAND FUNCTION -- DO NOT DELETE IT*/ \
	void(*visit)(); \
	void(*draw)(); \
	void(*add_child)(); \
	void(*set_visible)(); \
	void(*set_scale)(); \
	void(*set_size)(); \
	void(*set_position)(); \
	void(*set_anchor)(); \
	void(*set_quat)(); \
  content \
  );

#define EXTEND_M_NODE(type, func, content) \
  EXTEND_REF(type, func, \
  /*EXPAND FIELD -- DO NOT DELETE IT*/ \
	m_vector3 position; \
	m_vector3 anchor; \
	m_vector3 size; \
	m_vector3 scale; \
	m_matrix4 model; \
	m_matrix4 render_model; \
	quaternion quat; \
	weak_ref* parent; \
	m_list* children; \
	int transform_dirty; \
	int visible; \
  content \
  );

EXTEND_M_NODE_FUNC(m_node_func,);

EXTEND_M_NODE(m_node, m_node_func,);

void m_node_free(m_node* arg);
void m_node_init(m_node* arg);
/*EXPAND DECLARE INTERFACE FUNCTION -- DO NOT DELETE IT*/

void m_node_visit(m_node* arg_0, m_matrix4 arg_1, int arg_2);
void m_node_draw(m_node* arg_0);
void m_node_add_child(m_node* arg_0, m_node* arg_1);
void m_node_set_visible(m_node* arg_0, int arg_1);
void m_node_set_scale(m_node* arg_0, m_vector3 arg_1);
void m_node_set_size(m_node* arg_0, m_vector3 arg_1);
void m_node_set_position(m_node* arg_0, m_vector3 arg_1);
void m_node_set_anchor(m_node* arg_0, m_vector3 arg_1);
void m_node_set_quat(m_node* arg_0, quaternion arg_1);

#define INHERIT_M_NODE_FUNC \
  INHERIT_REF_FUNC, \
  /*EXPAND FUNCTION INTERFACE ASSIGMENT -- DO NOT DELETE IT*/ \
	.visit = m_node_visit, \
	.draw = m_node_draw, \
	.add_child = m_node_add_child, \
	.set_visible = m_node_set_visible, \
	.set_scale = m_node_set_scale, \
	.set_size = m_node_set_size, \
	.set_position = m_node_set_position, \
	.set_anchor = m_node_set_anchor, \
	.set_quat = m_node_set_quat, \
  .free = m_node_free

m_node* m_node_new();

#ifdef __cplusplus
}
#endif

#endif
