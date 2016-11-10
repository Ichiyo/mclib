#ifndef _M_NODE_H
#define _M_NODE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <math/math.h>
#include <base/ref.h>
#include <mstr/list.h>

#define NODE_FLAG_DIRTY_TRANSFORM 1

#define EXTEND_NODE_FUNC(type,content) \
	EXTEND_REF_FUNC(type, \
		void(*visit)(void*, m_matrix4, int); \
		void(*draw)(void*); \
		void(*add_child)(void*,void*); \
		void(*set_visible)(void*,int); \
		void(*set_scale)(void*,m_vector3); \
		void(*set_size)(void*,m_vector3); \
		void(*set_position)(void*,m_vector3); \
		void(*set_anchor)(void*,m_vector3); \
		void(*set_quat)(void*,quaternion); \
		content \
	);

/*
	note :
	- define parent by weak_ref to prevent circular dependency
	e.g :
	root<->parent<->node
	if node holds a strong reference to parent then parent will
	have lowest refcount equal 2, it may not be released normally:
		phase 1
			root : ref_count = 1 (hold by parent)
			parent : ref_count = 2 (hold by parent and node)
			node : ref_count = 1 (hold by parent)
		phase 2 - root calls release root
			root : ref_count = 0 : released
			parent : ref_count = 1 : unreleased (memory leak)
			node : ref_count = 1 : unreleased (memory leak)
*/
#define EXTEND_NODE(struct_type, func, content) \
	EXTEND_REF(struct_type, func, \
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

EXTEND_NODE_FUNC(g_node_func,);
EXTEND_NODE(g_node, g_node_func,);

/*
interface for subclass
*/
void free_node(g_node* node);
void visit_node(g_node* node, m_matrix4, int);
void node_add_child(g_node*, g_node*);
void init_node(g_node* node);
void node_set_visible(g_node* node,int);
void node_set_scale(g_node* node,m_vector3);
void node_set_size(g_node* node,m_vector3);
void node_set_position(g_node* node,m_vector3);
void node_set_anchor(g_node* node,m_vector3);
void node_set_quat(g_node* node,quaternion);

#define INHERIT_NODE_FUNC \
	BASE_REF_FUNC_INHERIT, \
	.free = free_node, \
	.visit = visit_node, \
	.add_child = node_add_child, \
	.set_visible = node_set_visible, \
	.set_scale = node_set_scale, \
	.set_size = node_set_size, \
	.set_position = node_set_position, \
	.set_anchor = node_set_anchor, \
	.set_quat = node_set_quat

g_node* node_new();

#ifdef __cplusplus
}
#endif

#endif
