#ifndef _M_M_MESH_SOURCE_H
#define _M_M_MESH_SOURCE_H

//EXPEND HEADER -- DO NOT DELETE THIS LINE
#include <base/ref.h>
#include <mstr/m_float_array.h>
#include <mstr/string.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EXTEND_M_MESH_SOURCE_FUNC(type, content) \
  EXTEND_REF_FUNC(type, \
  /*EXPAND FUNCTION -- DO NOT DELETE IT*/ \
  content \
  );

#define EXTEND_M_MESH_SOURCE(type, func, content) \
  EXTEND_REF(type, func, \
  /*EXPAND FIELD -- DO NOT DELETE IT*/ \
	m_float_array* farr; \
	int count; \
	int stride; \
	m_string* source_id; \
	m_string* farr_id; \
  content \
  );

EXTEND_M_MESH_SOURCE_FUNC(m_mesh_source_func,);

EXTEND_M_MESH_SOURCE(m_mesh_source, m_mesh_source_func,);

void m_mesh_source_free(m_mesh_source* arg);
void m_mesh_source_init(m_mesh_source* arg);
/*EXPAND DECLARE INTERFACE FUNCTION -- DO NOT DELETE IT*/


#define INHERIT_M_MESH_SOURCE_FUNC \
  INHERIT_REF_FUNC, \
  /*EXPAND FUNCTION INTERFACE ASSIGMENT -- DO NOT DELETE IT*/ \
  .free = m_mesh_source_free

m_mesh_source* m_mesh_source_new();

#ifdef __cplusplus
}
#endif

#endif
