#include <graphic/skin3d/m_geometry_mesh.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"

void m_geometry_mesh_free(m_geometry_mesh* node)
{
  QUICK_RELEASE(node->id);
  QUICK_RELEASE(node->name);
  QUICK_RELEASE(node->sources);
  QUICK_RELEASE(node->vertices);
  QUICK_RELEASE(node->polylist);
  free(node);
}

/*EXPEND IMPLEMENTATION -- DO NOT DELETE THIS LINE*/

void m_geometry_mesh_add_source(m_geometry_mesh* arg_0, m_mesh_source* arg_1)
{
	arg_0->sources->func->push(arg_0->sources, arg_1, 1);
}

void m_geometry_mesh_set_vertices(m_geometry_mesh* arg_0, m_mesh_vertices* arg_1)
{
	QUICK_RELEASE(arg_0->vertices);
  arg_0->vertices = arg_1;
  QUICK_RETAIN(arg_0->vertices);
}

void m_geometry_mesh_set_polylist(m_geometry_mesh* arg_0, m_mesh_polylist* arg_1)
{
	QUICK_RELEASE(arg_0->polylist);
  arg_0->polylist = arg_1;
  QUICK_RETAIN(arg_0->polylist);
}

static m_geometry_mesh_func base_m_geometry_mesh_func =
{
  INHERIT_M_GEOMETRY_MESH_FUNC
};

void m_geometry_mesh_init(m_geometry_mesh* node)
{
	node->func = &base_m_geometry_mesh_func;
  node->id = new_string();
  QUICK_RETAIN(node->id);
  node->name = new_string();
  QUICK_RETAIN(node->name);
  node->sources = array_list_new();
  QUICK_RETAIN(node->sources);
}

m_geometry_mesh* m_geometry_mesh_new()
{
	REF_NEW_AUTO_RELEASE(m_geometry_mesh, node)

  m_geometry_mesh_init(node);
	return node;
}

#pragma GCC diagnostic pop

#ifdef __cplusplus
}
#endif
