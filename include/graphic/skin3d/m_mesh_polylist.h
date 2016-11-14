#ifndef _M_M_MESH_POLYLIST_H
#define _M_M_MESH_POLYLIST_H

//EXPEND HEADER -- DO NOT DELETE THIS LINE
#include <base/ref.h>
#include <mstr/list.h>
#include <mstr/m_int_array.h>
#include <graphic/skin3d/m_mesh_source.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EXTEND_M_MESH_POLYLIST_FUNC(type, content) \
  EXTEND_REF_FUNC(type, \
  /*EXPAND FUNCTION -- DO NOT DELETE IT*/ \
	void(*add_source)(void*, void*, void*, int); \
  content \
  );

#define EXTEND_M_MESH_POLYLIST(type, func, content) \
  EXTEND_REF(type, func, \
  /*EXPAND FIELD -- DO NOT DELETE IT*/ \
	m_list* sources; \
	m_list* semantics; \
	m_int_array* offsets; \
	m_int_array* vcount; \
	m_int_array* p; \
  content \
  );

EXTEND_M_MESH_POLYLIST_FUNC(m_mesh_polylist_func,);

EXTEND_M_MESH_POLYLIST(m_mesh_polylist, m_mesh_polylist_func,);

void m_mesh_polylist_free(m_mesh_polylist* arg);
void m_mesh_polylist_init(m_mesh_polylist* arg);
/*EXPAND DECLARE INTERFACE FUNCTION -- DO NOT DELETE IT*/

void m_mesh_polylist_add_source(m_mesh_polylist* arg_0, m_mesh_source* arg_1, m_string* arg_2, int arg_3);

#define INHERIT_M_MESH_POLYLIST_FUNC \
  INHERIT_REF_FUNC, \
  /*EXPAND FUNCTION INTERFACE ASSIGMENT -- DO NOT DELETE IT*/ \
	.add_source = m_mesh_polylist_add_source, \
  .free = m_mesh_polylist_free

m_mesh_polylist* m_mesh_polylist_new();

#ifdef __cplusplus
}
#endif

#endif
