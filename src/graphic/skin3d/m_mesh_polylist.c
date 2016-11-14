#include <graphic/skin3d/m_mesh_polylist.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"

void m_mesh_polylist_free(m_mesh_polylist* node)
{
	QUICK_RELEASE(node->sources);
  QUICK_RELEASE(node->semantics);
  QUICK_RELEASE(node->offsets);
  QUICK_RELEASE(node->vcount);
  QUICK_RELEASE(node->p);
  free(node);
}

/*EXPEND IMPLEMENTATION -- DO NOT DELETE THIS LINE*/


void m_mesh_polylist_add_source(m_mesh_polylist* node, m_mesh_source* source, m_string* semantic, int offset)
{
	node->sources->func->push(node->sources, source, 1);
  node->semantics->func->push(node->semantics, new_string_from_str(semantic), 1);
  node->offsets->func->push(node->offsets, offset);
}

static m_mesh_polylist_func base_m_mesh_polylist_func =
{
  INHERIT_M_MESH_POLYLIST_FUNC
};

void m_mesh_polylist_init(m_mesh_polylist* node)
{
	node->func = &base_m_mesh_polylist_func;

  node->sources = array_list_new();
  QUICK_RETAIN(node->sources);
  node->semantics = array_list_new();
  QUICK_RETAIN(node->semantics);
  node->offsets = m_int_array_new();
  QUICK_RETAIN(node->offsets);
  node->vcount = m_int_array_new();
  QUICK_RETAIN(node->vcount);
  node->p = m_int_array_new();
  QUICK_RETAIN(node->p);
}

m_mesh_polylist* m_mesh_polylist_new()
{
	REF_NEW_AUTO_RELEASE(m_mesh_polylist, node)

  m_mesh_polylist_init(node);
	return node;
}

#pragma GCC diagnostic pop

#ifdef __cplusplus
}
#endif
