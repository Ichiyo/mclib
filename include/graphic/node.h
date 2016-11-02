#ifndef _M_NODE_H
#define _M_NODE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <math/math.h>
#include <base/ref.h>

struct _g_node_func
{
	REF_FUNC_MACRO
	void(*visit)(void*);
	void(*draw)(void*, void*);
	void(*free_render_data)(void*, void*);
};
typedef struct _g_node_func g_node_func;

struct _g_node
{
	CONSTRUCT_REF(g_node_func)
	vector3 position;
	vector3 anchor;
	vector2 size;
	quaternion quat;
	matrix4 model;
	void* render_data;

	struct _g_node* parent;
	struct _g_node* child;
	struct _g_node* next_sibling;
};
typedef struct _g_node g_node;

g_node* node_new();

#ifdef __cplusplus
}
#endif

#endif
