#ifndef _M_NODE_3D_H
#define _M_NODE_3D_H

#include <graphic/node.h>
#include <graphic/graphic.h>
#include <graphic/texture.h>
#include <graphic/shader.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EXTEND_NODE3D_FUNC(type, content) \
  EXTEND_NODE_FUNC(type, \
    void(*set_shader)(void*,void*); \
    void(*set_texture)(void*,void*); \
    void(*set_model_obj)(void*,char*); \
    content \
  );

#define EXTEND_NODE3D(type, func, content) \
  EXTEND_NODE(type, func, \
    GLuint vbo; \
    GLuint ebo; \
    GLuint vao; \
    int count; \
    g_shader* shader; \
    g_texture* texture; \
    content \
  );

EXTEND_NODE3D_FUNC(g_node3d_func,);

EXTEND_NODE3D(g_node3d, g_node3d_func,);

void node3d_free(g_node3d* node);
void node3d_set_shader(g_node3d* node, g_shader* shader);
void node3d_set_texture(g_node3d* node, g_texture* texture);
void node3d_draw(g_node3d* node);
void node3d_set_model_obj(g_node3d* node, char* file);
void init_node3d(g_node3d* node);

#define INHERIT_node3d_FUNC \
	INHERIT_NODE_FUNC, \
	.free = node3d_free, \
	.set_shader = node3d_set_shader, \
  .set_texture = node3d_set_texture, \
  .set_model_obj = node3d_set_model_obj, \
  .draw = node3d_draw

g_node* node3d_new();

#ifdef __cplusplus
}
#endif

#endif
