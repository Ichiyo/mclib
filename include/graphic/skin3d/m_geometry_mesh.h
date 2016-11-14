#ifndef _M_M_GEOMETRY_MESH_H
#define _M_M_GEOMETRY_MESH_H

//EXPEND HEADER -- DO NOT DELETE THIS LINE
#include <base/ref.h>
#include <mstr/string.h>
#include <mstr/list.h>
#include <graphic/skin3d/m_mesh_source.h>
#include <graphic/skin3d/m_mesh_vertices.h>
#include <graphic/skin3d/m_mesh_polylist.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EXTEND_M_GEOMETRY_MESH_FUNC(type, content) \
  EXTEND_REF_FUNC(type, \
  /*EXPAND FUNCTION -- DO NOT DELETE IT*/ \
	void(*add_source)(void*, void*); \
	void(*set_vertices)(void*, void*); \
	void(*set_polylist)(void*, void*); \
  content \
  );

#define EXTEND_M_GEOMETRY_MESH(type, func, content) \
  EXTEND_REF(type, func, \
  /*EXPAND FIELD -- DO NOT DELETE IT*/ \
	m_string* id; \
	m_string* name; \
	m_list* sources; \
	m_mesh_vertices* vertices; \
	m_mesh_polylist* polylist; \
  content \
  );

EXTEND_M_GEOMETRY_MESH_FUNC(m_geometry_mesh_func,);

EXTEND_M_GEOMETRY_MESH(m_geometry_mesh, m_geometry_mesh_func,);

void m_geometry_mesh_free(m_geometry_mesh* arg);
void m_geometry_mesh_init(m_geometry_mesh* arg);
/*EXPAND DECLARE INTERFACE FUNCTION -- DO NOT DELETE IT*/
void m_geometry_mesh_add_source(m_geometry_mesh* arg_0, m_mesh_source* arg_1);
void m_geometry_mesh_set_vertices(m_geometry_mesh* arg_0, m_mesh_vertices* arg_1);
void m_geometry_mesh_set_polylist(m_geometry_mesh* arg_0, m_mesh_polylist* arg_1);


#define INHERIT_M_GEOMETRY_MESH_FUNC \
  INHERIT_REF_FUNC, \
  /*EXPAND FUNCTION INTERFACE ASSIGMENT -- DO NOT DELETE IT*/ \
	.add_source = m_geometry_mesh_add_source, \
	.set_vertices = m_geometry_mesh_set_vertices, \
	.set_polylist = m_geometry_mesh_set_polylist, \
  .free = m_geometry_mesh_free

m_geometry_mesh* m_geometry_mesh_new();

#ifdef __cplusplus
}
#endif

#endif
