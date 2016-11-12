#include <graphic/node.h>
#include <graphic/sprite2d.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

void sprite2d_free(g_sprite2d* node)
{
	if(node->ebo) glDeleteBuffers(1, &node->ebo);
  if(node->vbo) glDeleteBuffers(1, &node->vbo);
  if(node->vao) glDeleteVertexArrays(1, &node->vao);
	if(node->shader) node->shader->func->release(node->shader);
	if(node->texture) node->texture->func->release(node->texture);
	free_node(node);
}

void sprite2d_set_shader(g_sprite2d* node, m_shader* shader)
{
	if(node->shader) node->shader->func->release(node->shader);
	node->shader = shader;
	if(node->shader) node->shader->func->retain(node->shader);
	node->shader->func->use(node->shader);

	glBindBuffer(GL_ARRAY_BUFFER, node->vbo);
	glBindVertexArray(node->vao);

	GLint posAttrib = glGetAttribLocation(shader->func->get_id(shader), "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

	GLint texAttrib = glGetAttribLocation(shader->func->get_id(shader), "texcoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void sprite2d_set_texture(g_sprite2d* node, m_texture* texture)
{
	if(node->texture) node->texture->func->release(node->texture);
	node->texture = texture;
	if(node->texture) node->texture->func->retain(node->texture);
}

void sprite2d_draw(g_sprite2d* node)
{
	if(node->shader) node->shader->func->use(node->shader);
	else return;
	if(node->texture) node->texture->func->bind(node->texture, 0);
	else return;

	GLint uniModel = glGetUniformLocation(node->shader->func->get_id(node->shader), "model");
	glUniformMatrix4fv(uniModel, 1, GL_FALSE, node->render_model.m);

	glBindVertexArray(node->vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"

static g_sprite2d_func base_g_sprite_func =
{
  INHERIT_SPRITE2D_FUNC
};

void init_sprite2d(g_sprite2d* node)
{
	node->func = &base_g_sprite_func;
	GLfloat vertices[] = {
	// Pos      // Tex
		-0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f, -0.5f, 0.0f, 1.0f,

		-0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, -0.5f, 1.0f, 1.0f
	};

	glGenVertexArrays(1, &node->vao);
	glGenBuffers(1, &node->vbo);

	glBindBuffer(GL_ARRAY_BUFFER, node->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(node->vao);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

#pragma GCC diagnostic pop

g_node* sprite2d_new()
{
	REF_NEW_AUTO_RELEASE(g_sprite2d, node)
	init_node(node);
	init_sprite2d(node);
	return node;
}

#ifdef __cplusplus
}
#endif
