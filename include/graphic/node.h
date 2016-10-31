#ifndef _M_NODE_H
#define _M_NODE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <math/math.h>
#include <base/ref.h>

struct _g_node
{
	REF_MACRO
	vector3 position;
	vector3 anchor;
	vector2 size;
	quaternion quat;
	matrix4 model;
	void* render_data;

	struct _g_node* parent;
	struct _g_node* child;
	struct _g_node* next_sibling;

	void(*visit)(struct _g_node*);
	void(*draw)(struct _g_node*, void*);
	void(*free_render_data)(struct _g_node*, void*);
};
typedef struct _g_node g_node;

g_node* node_new();

#ifdef __cplusplus
}
#endif

#endif
