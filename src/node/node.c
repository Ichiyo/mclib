#include <graphic/node.h>
#include <graphic/sprite2d.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

void free_node(g_node* node)
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

void visit_node(g_node* node, matrix4 current_model, int flag)
{
	if(!node->visible) return;

	flag = flag | node->transform_dirty;
	if(flag)
	{
		matrix4 model = matrix4_identity;
		model = matrix4_translate_vector3(model, node->position);

		model = matrix4_translate_vector3(model, vector3_new(node->anchor.v[0] * node->size.v[0], node->anchor.v[1] * node->size.v[1], node->anchor.v[2] * node->size.v[2]));
		model = matrix4_mul(model, matrix4_create_quaternion(node->quat));
		model = matrix4_translate_vector3(model, vector3_new(-node->anchor.v[0] * node->size.v[0], -node->anchor.v[1] * node->size.v[1], node->anchor.v[2] * node->size.v[2]));
		model = matrix4_scale_vector3(model, node->scale);
		model = matrix4_mul(current_model, model);
		node->render_model = matrix4_scale_vector3(model, node->size);
		node->model= matrix4_translate_vector3(model, vector3_new(-node->anchor.v[0] * node->size.v[0], -node->anchor.v[1] * node->size.v[1], node->anchor.v[2] * node->size.v[2]));
		node->transform_dirty = 0;
	}

	if(node->func->draw) node->func->draw(node);
	if(node->children)
	{
		long size = node->children->size;
		for(long i = 0; i < size; i++)
		{
			g_node* child = (g_node*)node->children->func->get_index(node->children, i);
			child->func->visit(child, node->model, flag);
		}
	}
}

void node_add_child(g_node* node, g_node* child)
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

void node_set_visible(g_node* node,int visible)
{
	node->visible = visible;
}

void node_set_scale(g_node* node,vector3 vector)
{
	node->scale = vector;
	node->transform_dirty = 1;
}

void node_set_size(g_node* node,vector3 vector)
{
	node->size = vector;
	node->transform_dirty = 1;
}

void node_set_position(g_node* node,vector3 vector)
{
	node->position = vector;
	node->transform_dirty = 1;
}

void node_set_anchor(g_node* node, vector3 vector)
{
	node->anchor = vector;
	node->transform_dirty = 1;
}

void node_set_quat(g_node* node,quaternion quat)
{
	node->quat = quat;
	node->transform_dirty = 1;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"

g_node_func base_g_node_func =
{
	BASE_REF_FUNC_INHERIT,
	.visit = visit_node,
	.free = free_node,
	.draw = 0,
	.add_child = node_add_child
};

void init_node(g_node* node)
{
	// default attributes
	node->model = matrix4_identity;
	node->anchor = vector3_new(0.5, 0.5, 0.5);
	node->scale = vector3_new(1, 1, 1);
	node->transform_dirty = 1;
	node->quat = quaternion_identity;
	node->visible = 1;
	// default behaviors
	node->func = &base_g_node_func;
}

g_node* node_new()
{
	REF_NEW_AUTO_RELEASE(g_node, node)
	init_node(node);
	return node;
}
#pragma GCC diagnostic pop

#ifdef __cplusplus
}
#endif
