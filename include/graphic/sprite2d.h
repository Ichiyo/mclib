#ifndef _M_SPRITE2D_H
#define _M_SPRITE2D_H

#include <graphic/node.h>

#ifdef __cplusplus
extern "C" {
#endif

struct _Sprite2dRenderData
{
  int data;
};
typedef struct _Sprite2dRenderData sprite2d_render_data;

struct g_node* sprite2d_new();

#ifdef __cplusplus
}
#endif

#endif
