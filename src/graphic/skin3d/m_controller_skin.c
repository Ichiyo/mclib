#include <graphic/skin3d/m_controller_skin.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"

void m_controller_skin_free(m_controller_skin* node)
{
  QUICK_RELEASE(node->id);
  QUICK_RELEASE(node->name);
  QUICK_RELEASE(node->mesh);
  QUICK_RELEASE(node->join_names);
  QUICK_RELEASE(node->bind_poses);
  QUICK_RELEASE(node->weights);
  QUICK_RELEASE(node->vcount);
  QUICK_RELEASE(node->v);
	free(node);
}

/*EXPEND IMPLEMENTATION -- DO NOT DELETE THIS LINE*/

void m_controller_skin_set_mesh(m_controller_skin* arg_0, m_geometry_mesh* arg_1)
{
	QUICK_RELEASE(arg_0->mesh);
  arg_0->mesh = arg_1;
  QUICK_RETAIN(arg_0->mesh);
}


static m_controller_skin_func base_m_controller_skin_func =
{
  INHERIT_M_CONTROLLER_SKIN_FUNC
};

void m_controller_skin_init(m_controller_skin* node)
{
	node->func = &base_m_controller_skin_func;
  //TODO init
  node->id = new_string();
  QUICK_RETAIN(node->id);
  node->name = new_string();
  QUICK_RETAIN(node->name);
  node->join_names = array_list_new();
  QUICK_RETAIN(node->join_names);
  node->bind_poses = m_generic_array_new();
  QUICK_RETAIN(node->bind_poses);
  node->weights = m_generic_array_new();
  QUICK_RETAIN(node->weights);
  node->vcount = m_generic_array_new();
  QUICK_RETAIN(node->vcount);
  node->v = m_generic_array_new();
  QUICK_RETAIN(node->v);
}

m_controller_skin* m_controller_skin_new()
{
	REF_NEW_AUTO_RELEASE(m_controller_skin, node)

  m_controller_skin_init(node);
	return node;
}

#pragma GCC diagnostic pop

#ifdef __cplusplus
}
#endif
