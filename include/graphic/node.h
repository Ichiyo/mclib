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
	void(*draw)(void*);
};
typedef struct _g_node_func g_node_func;

#define CONSTRUCT_G_NODE(func) \
	CONSTRUCT_REF(func) \
	vector3 position; \
	vector3 anchor; \
	vector2 size; \
	quaternion quat; \
	matrix4 model; \
	struct _g_node* parent; \
	struct _g_node* child; \
	struct _g_node* next_sibling; \

struct _g_node
{
	CONSTRUCT_G_NODE(g_node_func)
};
typedef struct _g_node g_node;

g_node* node_new();

#ifdef __cplusplus
}
#endif

#endif
