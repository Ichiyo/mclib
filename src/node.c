#include <graphic/node.h>
#include <graphic/sprite2d.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

static void free_node(struct g_node* node)
{
	if(node->free_render_data) node->free_render_data(node, node->render_data);
	free(node);
}

static void visit_node(struct g_node* node)
{
	if(node->draw) node->draw(node, node->render_data);
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
static void init_node(struct g_node* node)
{
	ref_init(node);
	// default attributes
	node->quat = quaternion_identity;
	node->model = matrix4_identity;
	// default behaviors
	node->visit = visit_node;
	node->free = free_node;
}
#pragma GCC diagnostic pop

struct g_node* node_new()
{
	struct g_node* node = calloc(1, sizeof(struct g_node));
	init_node(node);
	node->auto_release(node);
	return node;
}

/*
*	implement sprite 2d
*/

static void sprite2d_draw(struct g_node* node, sprite2d_render_data* data)
{
	printf("Hi sprite is drawing %d\n", data->data);
}

static void sprite2d_free_render_data(struct g_node* node, sprite2d_render_data* data)
{
	free(data);
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
static void init_sprite2d(struct g_node* node)
{
	sprite2d_render_data* data = calloc(1, sizeof(sprite2d_render_data));
	data->data = 123;
	node->render_data = data;
	node->draw = sprite2d_draw;
	node->free_render_data = sprite2d_free_render_data;
}
#pragma GCC diagnostic pop

struct g_node* sprite2d_new()
{
	struct g_node* node = node_new();
	init_sprite2d(node);
	return node;
}

#ifdef __cplusplus
}
#endif
