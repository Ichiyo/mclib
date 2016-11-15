#ifndef _M_M_VISUAL_SCENE_JOIN_H
#define _M_M_VISUAL_SCENE_JOIN_H

//EXPEND HEADER -- DO NOT DELETE THIS LINE
#include <base/ref.h>
#include <mstr/string.h>
#include <mstr/list.h>
#include <math/math.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EXTEND_M_VISUAL_SCENE_JOIN_FUNC(type, content) \
  EXTEND_REF_FUNC(type, \
  /*EXPAND FUNCTION -- DO NOT DELETE IT*/ \
	void(*add_child)(void*, void*); \
  content \
  );

#define EXTEND_M_VISUAL_SCENE_JOIN(type, func, content) \
  EXTEND_REF(type, func, \
  /*EXPAND FIELD -- DO NOT DELETE IT*/ \
	m_string* id; \
	m_string* name; \
	m_string* sid; \
	m_matrix4 transform; \
	m_list* children; \
	weak_ref* parent; \
  content \
  );

EXTEND_M_VISUAL_SCENE_JOIN_FUNC(m_visual_scene_join_func,);

EXTEND_M_VISUAL_SCENE_JOIN(m_visual_scene_join, m_visual_scene_join_func,);

void m_visual_scene_join_free(m_visual_scene_join* arg);
void m_visual_scene_join_init(m_visual_scene_join* arg);
/*EXPAND DECLARE INTERFACE FUNCTION -- DO NOT DELETE IT*/
void m_visual_scene_join_add_child(m_visual_scene_join* arg_0, m_visual_scene_join* arg_1);


#define INHERIT_M_VISUAL_SCENE_JOIN_FUNC \
  INHERIT_REF_FUNC, \
  /*EXPAND FUNCTION INTERFACE ASSIGMENT -- DO NOT DELETE IT*/ \
	.add_child = m_visual_scene_join_add_child, \
  .free = m_visual_scene_join_free

m_visual_scene_join* m_visual_scene_join_new();

#ifdef __cplusplus
}
#endif

#endif
