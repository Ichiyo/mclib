#include <graphic/m_node.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"

void m_node_free(m_node* node)
{
  if(node->children)
	{
		node->children->func->release(node->children);
	}
	if(node->parent)
	{
		node->parent->func->release(node->parent);
	}
	node->children = 0;
	node->parent = 0;
	free(node);
}

/*EXPEND IMPLEMENTATION -- DO NOT DELETE THIS LINE*/


void m_node_visit(m_node* node, m_matrix4 current_model, int flag)
{
  if(!node->visible) return;

	flag = flag | node->transform_dirty;
	if(flag)
	{
		m_matrix4 model = matrix4_identity;
		model = matrix4_translate_vector3(model, node->position);
    model = matrix4_mul(model,node->fix_model);
		model = matrix4_mul(model,matrix4_create_quaternion(node->quat));
		model = matrix4_scale_vector3(model, node->scale);
    node->render_model = model;
    node->render_model = matrix4_mul(current_model, node->render_model);
    node->render_model = matrix4_scale_vector3(node->render_model, node->size);
    model= matrix4_translate_vector3(model, vector3_new(-node->anchor.v[0] * node->size.v[0], -node->anchor.v[1] * node->size.v[1], -node->anchor.v[2] * node->size.v[2]));
		model = matrix4_mul(current_model, model);
    node->model = model;
		node->transform_dirty = 0;
	}

	if(node->func->draw) node->func->draw(node);
	if(node->children)
	{
		long size = node->children->size;
		for(long i = 0; i < size; i++)
		{
			m_node* child = (m_node*)node->children->func->get_index(node->children, i);
			child->func->visit(child, node->model, flag);
		}
	}
}

void m_node_draw(m_node* arg_0)
{
	//TODO implement
}

void m_node_add_child(m_node* node, m_node* child)
{
  if(!node->children)
	{
		node->children = array_list_new();
		node->children->func->retain(node->children);
	}
	node->children->func->push(node->children, child, 1);
	if(child->parent)
	{
		//TODO assert dangerous
	}
	child->parent = node->func->new_weak_ref(node);
	child->parent->func->retain(child->parent);
}

void m_node_set_visible(m_node* node, int visible)
{
	node->visible = visible;
}

void m_node_set_scale(m_node* node, m_vector3 vector)
{
  node->scale = vector;
	node->transform_dirty = 1;
}

void m_node_set_size(m_node* node, m_vector3 vector)
{
  node->size = vector;
	node->transform_dirty = 1;
}

void m_node_set_position(m_node* node, m_vector3 vector)
{
  node->position = vector;
	node->transform_dirty = 1;
}

void m_node_set_anchor(m_node* node, m_vector3 vector)
{
  node->anchor = vector;
	node->transform_dirty = 1;
}

void m_node_set_quat(m_node* node, quaternion quat)
{
  node->quat = quat;
	node->transform_dirty = 1;
}

static m_node_func base_m_node_func =
{
  INHERIT_M_NODE_FUNC
};

void m_node_init(m_node* node)
{
	node->func = &base_m_node_func;

  node->model = matrix4_identity;
  node->fix_model = matrix4_identity;
  node->anchor = vector3_new(0.5, 0.5, 0.5);
  node->scale = vector3_new(1, 1, 1);
  node->transform_dirty = 1;
  node->quat = quaternion_identity;
  node->visible = 1;
}

m_node* m_node_new()
{
	REF_NEW_AUTO_RELEASE(m_node, node)

  m_node_init(node);
	return node;
}

#pragma GCC diagnostic pop

#ifdef __cplusplus
}
#endif
