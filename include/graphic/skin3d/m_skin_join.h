#ifndef _M_M_SKIN_JOIN_H
#define _M_M_SKIN_JOIN_H

//EXPEND HEADER -- DO NOT DELETE THIS LINE
#include <base/ref.h>
#include <mstr/string.h>
#include <math/math.h>
#include <mstr/list.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EXTEND_M_SKIN_JOIN_FUNC(type, content) \
  EXTEND_REF_FUNC(type, \
  /*EXPAND FUNCTION -- DO NOT DELETE IT*/ \
	void(*add_child)(void*, void*); \
  content \
  );

#define EXTEND_M_SKIN_JOIN(type, func, content) \
  EXTEND_REF(type, func, \
  /*EXPAND FIELD -- DO NOT DELETE IT*/ \
	m_string* id; \
	m_matrix4 transform; \
	m_list* children; \
	weak_ref* parent; \
	m_matrix4 inverse_bind_pose; \
	m_matrix4 bind_pose; \
  m_matrix4 world_matrix; \
  m_matrix4 fix_leaf; \
  m_matrix4 local_animation; \
  m_matrix4 final_matrix; \
	m_string* name; \
  m_string* uniform_id; \
	m_string* sid; \
  content \
  );

EXTEND_M_SKIN_JOIN_FUNC(m_skin_join_func,);

EXTEND_M_SKIN_JOIN(m_skin_join, m_skin_join_func,);

void m_skin_join_free(m_skin_join* arg);
void m_skin_join_init(m_skin_join* arg);
/*EXPAND DECLARE INTERFACE FUNCTION -- DO NOT DELETE IT*/
void m_skin_join_add_child(m_skin_join* arg_0, m_skin_join* arg_1);


#define INHERIT_M_SKIN_JOIN_FUNC \
  INHERIT_REF_FUNC, \
  /*EXPAND FUNCTION INTERFACE ASSIGMENT -- DO NOT DELETE IT*/ \
	.add_child = m_skin_join_add_child, \
  .free = m_skin_join_free

m_skin_join* m_skin_join_new();

#ifdef __cplusplus
}
#endif

#endif
