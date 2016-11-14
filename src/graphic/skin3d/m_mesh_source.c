#include <graphic/skin3d/m_mesh_source.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"

void m_mesh_source_free(m_mesh_source* node)
{
	QUICK_RELEASE(node->farr);
  QUICK_RELEASE(node->source_id);
  QUICK_RELEASE(node->farr_id);
  free(node);
}

/*EXPEND IMPLEMENTATION -- DO NOT DELETE THIS LINE*/


static m_mesh_source_func base_m_mesh_source_func =
{
  INHERIT_M_MESH_SOURCE_FUNC
};

void m_mesh_source_init(m_mesh_source* node)
{
	node->func = &base_m_mesh_source_func;
  node->source_id = new_string();
  QUICK_RETAIN(node->source_id);
  node->farr_id = new_string();
  QUICK_RETAIN(node->farr_id);
  node->farr = m_float_array_new();
  QUICK_RETAIN(node->farr);
}

m_mesh_source* m_mesh_source_new()
{
	REF_NEW_AUTO_RELEASE(m_mesh_source, node)

  m_mesh_source_init(node);
	return node;
}

#pragma GCC diagnostic pop

#ifdef __cplusplus
}
#endif
