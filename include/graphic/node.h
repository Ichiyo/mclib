#ifndef _M_NODE_H
#define _M_NODE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <math/math.h>
#include <base/ref.h>

EXTEND_REF_FUNC(g_node_func,
	void(*visit)(void*);
	void(*draw)(void*);
);

#define EXTEND_NODE(struct_type, func, content) \
	EXTEND_REF(struct_type, func, \
		vector3 position; \
		vector3 anchor; \
		vector2 size; \
		quaternion quat; \
		matrix4 model; \
		struct _g_node* parent; \
		struct _g_node* child; \
		struct _g_node* next_sibling; \
		content \
	);

EXTEND_NODE(g_node, g_node_func,);

g_node* node_new();

#ifdef __cplusplus
}
#endif

#endif
