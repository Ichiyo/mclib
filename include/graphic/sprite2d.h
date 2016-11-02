#ifndef _M_SPRITE2D_H
#define _M_SPRITE2D_H

#include <graphic/node.h>

#ifdef __cplusplus
extern "C" {
#endif

struct _g_sprite2d
{
  CONSTRUCT_G_NODE(g_node_func)
  int data;
};
typedef struct _g_sprite2d g_sprite2d;

g_node* sprite2d_new();

#ifdef __cplusplus
}
#endif

#endif
