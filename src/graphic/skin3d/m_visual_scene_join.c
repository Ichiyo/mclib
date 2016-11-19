#include <graphic/skin3d/m_visual_scene_join.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"

void m_visual_scene_join_free(m_visual_scene_join* node)
{
  QUICK_RELEASE(node->id);
  QUICK_RELEASE(node->name);
  QUICK_RELEASE(node->sid);
  QUICK_RELEASE(node->children);
  QUICK_RELEASE(node->parent);
	free(node);
}

/*EXPEND IMPLEMENTATION -- DO NOT DELETE THIS LINE*/

void m_visual_scene_join_add_child(m_visual_scene_join* node, m_visual_scene_join* join)
{
	node->children->func->push(node->children, join, 1);
  QUICK_RELEASE(join->parent);
  join->parent = node->func->new_weak_ref(node);
  QUICK_RETAIN(join->parent);
}


static m_visual_scene_join_func base_m_visual_scene_join_func =
{
  INHERIT_M_VISUAL_SCENE_JOIN_FUNC
};

void m_visual_scene_join_init(m_visual_scene_join* node)
{
	node->func = &base_m_visual_scene_join_func;
  node->transform = matrix4_identity;
  node->id = new_string();
  QUICK_RETAIN(node->id);
  node->name = new_string();
  QUICK_RETAIN(node->name);
  node->sid = new_string();
  QUICK_RETAIN(node->sid);
  node->children = array_list_new();
  QUICK_RETAIN(node->children);
}

m_visual_scene_join* m_visual_scene_join_new()
{
	REF_NEW_AUTO_RELEASE(m_visual_scene_join, node)

  m_visual_scene_join_init(node);
	return node;
}

#pragma GCC diagnostic pop

#ifdef __cplusplus
}
#endif
