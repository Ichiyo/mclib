#include <graphic/skin3d/m_skin_join.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"

void m_skin_join_free(m_skin_join* node)
{
  QUICK_RELEASE(node->name);
  QUICK_RELEASE(node->sid);
  QUICK_RELEASE(node->id);
  QUICK_RELEASE(node->uniform_id);
  QUICK_RELEASE(node->parent);
  QUICK_RELEASE(node->children);
	free(node);
}

/*EXPEND IMPLEMENTATION -- DO NOT DELETE THIS LINE*/

void m_skin_join_add_child(m_skin_join* join, m_skin_join* in)
{
  if(in->parent)
  {
    //TODO error
  }
  join->children->func->push(join->children, in, 1);
  in->parent = join->func->new_weak_ref(join);
  QUICK_RETAIN(in->parent);
}


static m_skin_join_func base_m_skin_join_func =
{
  INHERIT_M_SKIN_JOIN_FUNC
};

void m_skin_join_init(m_skin_join* node)
{
	node->func = &base_m_skin_join_func;
  node->bind_pose = matrix4_identity;
  node->transform = matrix4_identity;
  node->fix_leaf = matrix4_identity;
  node->local_animation = matrix4_identity;
  node->combine_local_animation = matrix4_identity;
  node->name = new_string();
  QUICK_RETAIN(node->name);
  node->sid = new_string();
  QUICK_RETAIN(node->sid);
  node->id = new_string();
  QUICK_RETAIN(node->id);
  node->uniform_id = new_string();
  QUICK_RETAIN(node->uniform_id);
  node->children = array_list_new();
  QUICK_RETAIN(node->children);
}

m_skin_join* m_skin_join_new()
{
	REF_NEW_AUTO_RELEASE(m_skin_join, node)

  m_skin_join_init(node);
	return node;
}

#pragma GCC diagnostic pop

#ifdef __cplusplus
}
#endif
