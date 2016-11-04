#ifndef _M_SPRITE2D_H
#define _M_SPRITE2D_H

#include <graphic/node.h>
#include <graphic/graphic.h>
#include <graphic/texture.h>
#include <graphic/shader.h>

#ifdef __cplusplus
extern "C" {
#endif

EXTEND_NODE_FUNC(g_sprite2d_func,
  void(*set_shader)(void*,void*);
  void(*set_texture)(void*,void*);
);

EXTEND_NODE(g_sprite2d, g_sprite2d_func,
  GLuint vbo;
  GLuint ebo;
  GLuint vao;
  g_shader* shader;
  g_texture* texture;
);

void sprite2d_free(g_sprite2d* node);
void sprite2d_set_shader(g_sprite2d* node, g_shader* shader);
void sprite2d_set_texture(g_sprite2d* node, g_texture* texture);
void sprite2d_draw(g_sprite2d* node);
void init_sprite2d(g_sprite2d* node);

#define INHERIT_SPRITE2D_FUNC \
	INHERIT_NODE_FUNC, \
	.free = sprite2d_free, \
	.set_shader = sprite2d_set_shader, \
  .set_texture = sprite2d_set_texture, \
  .draw = sprite2d_draw

g_node* sprite2d_new();

#ifdef __cplusplus
}
#endif

#endif
