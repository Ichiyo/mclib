#include <graphic/node.h>
#include <graphic/sprite2d.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

static void free_node(g_node* node)
{
	if(node->func->free_render_data) node->func->free_render_data(node, node->render_data);
	free(node);
}

static void visit_node(g_node* node)
{
	if(node->func->draw) node->func->draw(node, node->render_data);
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"

static g_node_func base_g_node_func =
{
	BASE_REF_FUNC_INHERIT,
	.visit = visit_node,
	.free = free_node,
	.draw = 0,
	.free_render_data = 0
};

static void init_node(g_node* node)
{
	// default attributes
	node->quat = quaternion_identity;
	node->model = matrix4_identity;
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
/*
*	implement sprite 2d
*/

static void sprite2d_draw(g_node* node, sprite2d_render_data* data)
{
	printf("Hi sprite is drawing %d\n", data->data);
}

static void sprite2d_free_render_data(g_node* node, sprite2d_render_data* data)
{
	free(data);
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"

static g_node_func base_g_sprite_func =
{
	BASE_REF_FUNC_INHERIT,
	.visit = visit_node,
	.free = free_node,
	.draw = sprite2d_draw,
	.free_render_data = sprite2d_free_render_data
};

static void init_sprite2d(g_node* node)
{
	sprite2d_render_data* data = calloc(1, sizeof(sprite2d_render_data));
	data->data = 123;
	node->render_data = data;
	node->func = &base_g_sprite_func;
}
#pragma GCC diagnostic pop

g_node* sprite2d_new()
{
	g_node* node = node_new();
	init_sprite2d(node);
	return node;
}

#ifdef __cplusplus
}
#endif
