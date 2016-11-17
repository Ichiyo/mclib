#ifndef _M_M_CONTROLLER_SKIN_H
#define _M_M_CONTROLLER_SKIN_H

//EXPEND HEADER -- DO NOT DELETE THIS LINE
#include <base/ref.h>
#include <mstr/list.h>
#include <math/math.h>
#include <graphic/skin3d/m_geometry_mesh.h>
#include <mstr/m_generic_array.h>
#include <mstr/string.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EXTEND_M_CONTROLLER_SKIN_FUNC(type, content) \
  EXTEND_REF_FUNC(type, \
  /*EXPAND FUNCTION -- DO NOT DELETE IT*/ \
	void(*set_mesh)(void*, void*); \
  content \
  );

#define EXTEND_M_CONTROLLER_SKIN(type, func, content) \
  EXTEND_REF(type, func, \
  /*EXPAND FIELD -- DO NOT DELETE IT*/ \
	m_string* id; \
	m_string* name; \
	m_geometry_mesh* mesh; \
	m_matrix4 bind_shape_matrix; \
	m_list* join_names; \
	m_generic_array* inv_bind_poses; \
	m_generic_array* weights; \
	m_generic_array* vcount; \
	m_generic_array* v; \
  int max_vcount; \
  content \
  );

EXTEND_M_CONTROLLER_SKIN_FUNC(m_controller_skin_func,);

EXTEND_M_CONTROLLER_SKIN(m_controller_skin, m_controller_skin_func,);

void m_controller_skin_free(m_controller_skin* arg);
void m_controller_skin_init(m_controller_skin* arg);
/*EXPAND DECLARE INTERFACE FUNCTION -- DO NOT DELETE IT*/
void m_controller_skin_set_mesh(m_controller_skin* arg_0, m_geometry_mesh* arg_1);


#define INHERIT_M_CONTROLLER_SKIN_FUNC \
  INHERIT_REF_FUNC, \
  /*EXPAND FUNCTION INTERFACE ASSIGMENT -- DO NOT DELETE IT*/ \
	.set_mesh = m_controller_skin_set_mesh, \
  .free = m_controller_skin_free

m_controller_skin* m_controller_skin_new();

#ifdef __cplusplus
}
#endif

#endif
