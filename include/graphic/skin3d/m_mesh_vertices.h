#ifndef _M_M_MESH_VERTICES_H
#define _M_M_MESH_VERTICES_H

//EXPEND HEADER -- DO NOT DELETE THIS LINE
#include <base/ref.h>
#include <mstr/string.h>
#include <graphic/skin3d/m_mesh_source.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EXTEND_M_MESH_VERTICES_FUNC(type, content) \
  EXTEND_REF_FUNC(type, \
  /*EXPAND FUNCTION -- DO NOT DELETE IT*/ \
	void(*add_source)(void*, void*); \
  content \
  );

#define EXTEND_M_MESH_VERTICES(type, func, content) \
  EXTEND_REF(type, func, \
  /*EXPAND FIELD -- DO NOT DELETE IT*/ \
	m_string* id; \
	m_string* semantic; \
	m_mesh_source* source; \
  content \
  );

EXTEND_M_MESH_VERTICES_FUNC(m_mesh_vertices_func,);

EXTEND_M_MESH_VERTICES(m_mesh_vertices, m_mesh_vertices_func,);

void m_mesh_vertices_free(m_mesh_vertices* arg);
void m_mesh_vertices_init(m_mesh_vertices* arg);
/*EXPAND DECLARE INTERFACE FUNCTION -- DO NOT DELETE IT*/
void m_mesh_vertices_add_source(m_mesh_vertices* arg_0, m_mesh_source* arg_1);


#define INHERIT_M_MESH_VERTICES_FUNC \
  INHERIT_REF_FUNC, \
  /*EXPAND FUNCTION INTERFACE ASSIGMENT -- DO NOT DELETE IT*/ \
	.add_source = m_mesh_vertices_add_source, \
  .free = m_mesh_vertices_free

m_mesh_vertices* m_mesh_vertices_new();

#ifdef __cplusplus
}
#endif

#endif
