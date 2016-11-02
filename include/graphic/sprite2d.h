#ifndef _M_SPRITE2D_H
#define _M_SPRITE2D_H

#include <graphic/node.h>

#ifdef __cplusplus
extern "C" {
#endif

EXTEND_NODE(g_sprite2d, g_node_func,
  int data;
)

g_node* sprite2d_new();

#ifdef __cplusplus
}
#endif

#endif
