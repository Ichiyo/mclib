#include <graphic/skin3d/m_mesh_vertices.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"

void m_mesh_vertices_free(m_mesh_vertices* node)
{
  QUICK_RELEASE(node->id);
  QUICK_RELEASE(node->semantic);
  QUICK_RELEASE(node->source);
	free(node);
}

/*EXPEND IMPLEMENTATION -- DO NOT DELETE THIS LINE*/

void m_mesh_vertices_add_source(m_mesh_vertices* node, m_mesh_source* in)
{
	QUICK_RELEASE(node->source);
  node->source = in;
  QUICK_RETAIN(node->source);
}

static m_mesh_vertices_func base_m_mesh_vertices_func =
{
  INHERIT_M_MESH_VERTICES_FUNC
};

void m_mesh_vertices_init(m_mesh_vertices* node)
{
	node->func = &base_m_mesh_vertices_func;
  node->id = new_string();
  QUICK_RETAIN(node->id);
  node->semantic = new_string();
  QUICK_RETAIN(node->semantic);
}

m_mesh_vertices* m_mesh_vertices_new()
{
	REF_NEW_AUTO_RELEASE(m_mesh_vertices, node)

  m_mesh_vertices_init(node);
	return node;
}

#pragma GCC diagnostic pop

#ifdef __cplusplus
}
#endif
