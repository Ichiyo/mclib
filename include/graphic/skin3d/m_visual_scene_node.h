#ifndef _M_M_VISUAL_SCENE_NODE_H
#define _M_M_VISUAL_SCENE_NODE_H

//EXPEND HEADER -- DO NOT DELETE THIS LINE
#include <base/ref.h>
#include <mstr/list.h>
#include <mstr/string.h>
#include <graphic/skin3d/m_visual_scene_join.h>
#include <math/math.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EXTEND_M_VISUAL_SCENE_NODE_FUNC(type, content) \
  EXTEND_REF_FUNC(type, \
  /*EXPAND FUNCTION -- DO NOT DELETE IT*/ \
	void(*set_geometry_url)(void*, void*); \
	void(*add_child)(void*, void*); \
	void(*set_skeleton)(void*, void*); \
	void(*set_skin_url)(void*, void*); \
  content \
  );

#define EXTEND_M_VISUAL_SCENE_NODE(type, func, content) \
  EXTEND_REF(type, func, \
  /*EXPAND FIELD -- DO NOT DELETE IT*/ \
	m_string* geometry_url; \
	m_matrix4 transform; \
	m_string* id; \
	m_string* name; \
	m_string* url; \
	m_visual_scene_join* skeleton; \
	m_list* children; \
	weak_ref* parent; \
	m_vector3 position; \
	m_vector3 rotation; \
	m_vector3 scale; \
  content \
  );

EXTEND_M_VISUAL_SCENE_NODE_FUNC(m_visual_scene_node_func,);

EXTEND_M_VISUAL_SCENE_NODE(m_visual_scene_node, m_visual_scene_node_func,);

void m_visual_scene_node_free(m_visual_scene_node* arg);
void m_visual_scene_node_init(m_visual_scene_node* arg);
/*EXPAND DECLARE INTERFACE FUNCTION -- DO NOT DELETE IT*/
void m_visual_scene_node_set_geometry_url(m_visual_scene_node* arg_0, m_string* arg_1);

void m_visual_scene_node_add_child(m_visual_scene_node* arg_0, m_visual_scene_node* arg_1);
void m_visual_scene_node_set_skeleton(m_visual_scene_node* arg_0, m_visual_scene_join* arg_1);
void m_visual_scene_node_set_skin_url(m_visual_scene_node* arg_0, m_string* arg_1);

#define INHERIT_M_VISUAL_SCENE_NODE_FUNC \
  INHERIT_REF_FUNC, \
  /*EXPAND FUNCTION INTERFACE ASSIGMENT -- DO NOT DELETE IT*/ \
	.set_geometry_url = m_visual_scene_node_set_geometry_url, \
	.add_child = m_visual_scene_node_add_child, \
	.set_skeleton = m_visual_scene_node_set_skeleton, \
	.set_skin_url = m_visual_scene_node_set_skin_url, \
  .free = m_visual_scene_node_free

m_visual_scene_node* m_visual_scene_node_new();

#ifdef __cplusplus
}
#endif

#endif
