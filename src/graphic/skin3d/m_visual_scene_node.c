#include <graphic/skin3d/m_visual_scene_node.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"

void m_visual_scene_node_free(m_visual_scene_node* node)
{
  QUICK_RELEASE(node->id);
  QUICK_RELEASE(node->name);
  QUICK_RELEASE(node->url);
  QUICK_RELEASE(node->geometry_url);
  QUICK_RELEASE(node->skeleton);
  QUICK_RELEASE(node->children);
  QUICK_RELEASE(node->parent);
	free(node);
}

/*EXPEND IMPLEMENTATION -- DO NOT DELETE THIS LINE*/

void m_visual_scene_node_set_geometry_url(m_visual_scene_node* node, m_string* url)
{
	 node->geometry_url->func->clear(node->geometry_url);
   node->geometry_url->func->cat_str(node->geometry_url, url);
}


void m_visual_scene_node_add_child(m_visual_scene_node* node, m_visual_scene_node* in)
{
	node->children->func->push(node->children, in, 1);
  QUICK_RELEASE(in->parent);
  in->parent = node->func->new_weak_ref(node);
  QUICK_RETAIN(in->parent);
}

void m_visual_scene_node_set_skeleton(m_visual_scene_node* node, m_visual_scene_join* skeleton)
{
	node->skeleton = skeleton;
  QUICK_RETAIN(node->skeleton);
}

void m_visual_scene_node_set_skin_url(m_visual_scene_node* node, m_string* in)
{
	node->url->func->clear(node->url);
  node->url->func->cat_str(node->url, in);
}

static m_visual_scene_node_func base_m_visual_scene_node_func =
{
  INHERIT_M_VISUAL_SCENE_NODE_FUNC
};

void m_visual_scene_node_init(m_visual_scene_node* node)
{
	node->func = &base_m_visual_scene_node_func;
  node->id = new_string();
  QUICK_RETAIN(node->id);
  node->name = new_string();
  QUICK_RETAIN(node->name);
  node->url = new_string();
  QUICK_RETAIN(node->url);
  node->geometry_url = new_string();
  QUICK_RETAIN(node->geometry_url);
  node->children = array_list_new();
  QUICK_RETAIN(node->children);
  node->scale = vector3_new(1, 1, 1);
}

m_visual_scene_node* m_visual_scene_node_new()
{
	REF_NEW_AUTO_RELEASE(m_visual_scene_node, node)

  m_visual_scene_node_init(node);
	return node;
}

#pragma GCC diagnostic pop

#ifdef __cplusplus
}
#endif
