#include <graphic/m_sprite2d.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"

void m_sprite2d_free(m_sprite2d* node)
{
  if(node->ebo) glDeleteBuffers(1, &node->ebo);
  if(node->vbo) glDeleteBuffers(1, &node->vbo);
  if(node->vao) glDeleteVertexArrays(1, &node->vao);
	if(node->shader) node->shader->func->release(node->shader);
	if(node->texture) node->texture->func->release(node->texture);
	m_node_free(node);
}

/*EXPEND IMPLEMENTATION -- DO NOT DELETE THIS LINE*/

void m_sprite2d_draw(m_sprite2d* node)
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

void m_sprite2d_set_shader(m_sprite2d* node, m_shader* shader)
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

void m_sprite2d_set_texture(m_sprite2d* node, m_texture* texture)
{
  if(node->texture) node->texture->func->release(node->texture);
	node->texture = texture;
	if(node->texture) node->texture->func->retain(node->texture);
}

static m_sprite2d_func base_m_sprite2d_func =
{
  INHERIT_M_SPRITE2D_FUNC
};

void m_sprite2d_init(m_sprite2d* node)
{
	node->func = &base_m_sprite2d_func;

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

m_sprite2d* m_sprite2d_new()
{
	REF_NEW_AUTO_RELEASE(m_sprite2d, node)
  m_node_init(node);
  m_sprite2d_init(node);
	return node;
}

#pragma GCC diagnostic pop

#ifdef __cplusplus
}
#endif
