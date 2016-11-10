#include <graphic/node.h>
#include <graphic/node3d.h>
#include <stdlib.h>
#include <stdio.h>
#include <utils/file_utils.h>

#ifdef __cplusplus
extern "C" {
#endif

void node3d_free(g_node3d* node)
{
	if(node->ebo) glDeleteBuffers(1, &node->ebo);
  if(node->vbo) glDeleteBuffers(1, &node->vbo);
  if(node->vao) glDeleteVertexArrays(1, &node->vao);
	if(node->shader) node->shader->func->release(node->shader);
	if(node->texture) node->texture->func->release(node->texture);
	free_node(node);
}

void node3d_set_shader(g_node3d* node, g_shader* shader)
{
	if(node->shader) node->shader->func->release(node->shader);
	node->shader = shader;
	if(node->shader)
  {
    node->shader->func->retain(node->shader);
    node->shader->func->use(node->shader);

    glBindBuffer(GL_ARRAY_BUFFER, node->vbo);
    glBindVertexArray(node->vao);

    GLint posAttrib = glGetAttribLocation(shader->func->get_id(shader), "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), 0);

		GLint norAttrib = glGetAttribLocation(shader->func->get_id(shader), "normal");
		glEnableVertexAttribArray(norAttrib);
		glVertexAttribPointer(norAttrib, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

    GLint texAttrib = glGetAttribLocation(shader->func->get_id(shader), "texcoord");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));

		GLint modelAttrib = glGetAttribLocation(shader->func->get_id(shader), "model_index");
    glEnableVertexAttribArray(modelAttrib);
    glVertexAttribPointer(modelAttrib, 1, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (void*)(8 * sizeof(GLfloat)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }
}

void node3d_set_texture(g_node3d* node, g_texture* texture)
{
	if(node->texture) node->texture->func->release(node->texture);
	node->texture = texture;
	if(node->texture) node->texture->func->retain(node->texture);
}

void node3d_draw(g_node3d* node)
{
	if(node->shader) node->shader->func->use(node->shader);
	else return;
	if(node->texture) node->texture->func->bind(node->texture, 0);
	else return;

	GLint uniModel = glGetUniformLocation(node->shader->func->get_id(node->shader), "model[1]");
	glUniformMatrix4fv(uniModel, 1, GL_FALSE, node->render_model.m);

	glBindVertexArray(node->vao);
	glDrawArrays(GL_TRIANGLES, 0, node->count);
	glBindVertexArray(0);
}

void node3d_set_model_obj(g_node3d* node, char* path)
{
  FILE* file = open_file(path);
  if(!file) return;

  GLfloat* vertices = 0;
  GLfloat* normals = 0;
  GLfloat* uvs = 0;
  GLfloat* realvertices = 0;

	float model_index = 1;
  int realcount = 0;
  int uvcount = 2;
  int count = 3;
  int vcount = 3;
  char buff[1024];
  int has_texture = 0;
  while(fgets(buff, 1024, file))
  {
    if(buff[0] == 'v' && buff[1] == ' ')
    {
      char head;
      float x, y, z;
      sscanf(buff,"%c %f %f %f",&head,&x,&y,&z);
      vertices = realloc(vertices, count*sizeof(GLfloat));
      vertices[count-3] = x;
      vertices[count-2] = y;
      vertices[count-1] = z;
      count = count + 3;
    }
    else if(buff[0] == 'v' && buff[1] == 't')
    {
      has_texture = 1;
      char head1, head2;
      float u,v;
      sscanf(buff,"%c%c %f %f",&head1,&head2,&u,&v);
      uvs = realloc(uvs, uvcount*sizeof(GLfloat));
      uvs[uvcount-2] = u;
      uvs[uvcount-1] = v;
      uvcount = uvcount + 2;
    }
    else if(buff[0] == 'v' && buff[1] == 'n')
    {
      char head1, head2;
      float x, y, z;
      sscanf(buff,"%c%c %f %f %f",&head1,&head2,&x,&y,&z);
      normals = realloc(normals, vcount*sizeof(GLfloat));
      normals[vcount-3] = x;
      normals[vcount-2] = y;
      normals[vcount-1] = z;
      vcount = vcount + 3;
    }
    else if(buff[0] == 'f' && buff[1] == ' ')
    {
      char head;
      int v1,t1,n1,v2,t2,n2,v3,t3,n3;
      t1 = t2 = t3 = 1;
			n1 = n2 = n3 = 1;
      if(has_texture)
        sscanf(buff,"%c %d/%d/%d %d/%d/%d %d/%d/%d",&head,&v1,&t1,&n1,&v2,&t2,&n2,&v3,&t3,&n3);
      else
        sscanf(buff,"%c %d//%d %d//%d %d//%d",&head,&v1,&n1,&v2,&n2,&v3,&n3);
      v1 = (v1-1) * 3;
      v2 = (v2-1) * 3;
      v3 = (v3-1) * 3;
      t1 = (t1 - 1) * 2;
      t2 = (t2 - 1) * 2;
      t3 = (t3 - 1) * 2;
			n1 = (n1 - 1) * 3;
			n2 = (n2 - 1) * 3;
			n3 = (n3 - 1) * 3;
      realcount += 27; //(3 vertices + 3 normals + 2 uvs + 1 model) * 3
      realvertices = realloc(realvertices, realcount * sizeof(GLfloat));
			GLfloat* tt = (GLfloat*)realvertices;
      if(has_texture)
      {
        realvertices[realcount - 27] = vertices[v1];
        realvertices[realcount - 26] = vertices[v1+1];
        realvertices[realcount - 25] = vertices[v1+2];
				realvertices[realcount - 24] = normals[n1];
				realvertices[realcount - 23] = normals[n1+1];
				realvertices[realcount - 22] = normals[n1+2];
				realvertices[realcount - 21] = uvs[t1];
        realvertices[realcount - 20] = uvs[t1+1];
				tt[realcount - 19] = model_index;

				realvertices[realcount - 18] = vertices[v2];
        realvertices[realcount - 17] = vertices[v2+1];
        realvertices[realcount - 16] = vertices[v2+2];
				realvertices[realcount - 15] = normals[n2];
				realvertices[realcount - 14] = normals[n2+1];
				realvertices[realcount - 13] = normals[n2+2];
				realvertices[realcount - 12] = uvs[t2];
        realvertices[realcount - 11] = uvs[t2+1];
				tt[realcount - 10] = model_index;

				realvertices[realcount - 9] = vertices[v3];
        realvertices[realcount - 8] = vertices[v3+1];
        realvertices[realcount - 7] = vertices[v3+2];
				realvertices[realcount - 6] = normals[n3];
				realvertices[realcount - 5] = normals[n3+1];
				realvertices[realcount - 4] = normals[n3+2];
				realvertices[realcount - 3] = uvs[t3];
        realvertices[realcount - 2] = uvs[t3+1];
				tt[realcount - 1] = model_index;
      }
      else
      {
				realvertices[realcount - 27] = vertices[v1];
        realvertices[realcount - 26] = vertices[v1+1];
        realvertices[realcount - 25] = vertices[v1+2];
				realvertices[realcount - 24] = normals[n1];
				realvertices[realcount - 23] = normals[n1+1];
				realvertices[realcount - 22] = normals[n1+2];
				realvertices[realcount - 21] = 0;
        realvertices[realcount - 20] = 0;
				tt[realcount - 19] = model_index;

				realvertices[realcount - 18] = vertices[v2];
        realvertices[realcount - 17] = vertices[v2+1];
        realvertices[realcount - 16] = vertices[v2+2];
				realvertices[realcount - 15] = normals[n2];
				realvertices[realcount - 14] = normals[n2+1];
				realvertices[realcount - 13] = normals[n2+2];
				realvertices[realcount - 12] = 0;
        realvertices[realcount - 11] = 0;
				tt[realcount - 10] = model_index;

				realvertices[realcount - 9] = vertices[v3];
        realvertices[realcount - 8] = vertices[v3+1];
        realvertices[realcount - 7] = vertices[v3+2];
				realvertices[realcount - 6] = normals[n3];
				realvertices[realcount - 5] = normals[n3+1];
				realvertices[realcount - 4] = normals[n3+2];
				realvertices[realcount - 3] = 0;
        realvertices[realcount - 2] = 0;
				tt[realcount - 1] = model_index;
      }
    }
  }
  count = count - 3;
  vcount = vcount - 3;
  uvcount = uvcount - 2;
  fclose(file);
  if(realvertices)
  {
    node->count = realcount / 9;
    glBindBuffer(GL_ARRAY_BUFFER, node->vbo);
  	glBufferData(GL_ARRAY_BUFFER, realcount * sizeof(GLfloat), realvertices, GL_STATIC_DRAW);
  	glBindBuffer(GL_ARRAY_BUFFER, 0);
    node->func->set_shader(node, node->shader);
  }
  if(vertices) free(vertices);
  if(normals) free(normals);
  if(realvertices) free(realvertices);
  if(uvs) free(uvs);
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"

static g_node3d_func base_g_sprite_func =
{
  INHERIT_node3d_FUNC
};

void init_node3d(g_node3d* node)
{
	node->func = &base_g_sprite_func;
	GLfloat vertices[] = {
    -0.5f, -0.5f, -0.5f, 0.0, 0.0, 0.0, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f, 0.0, 0.0, 0.0, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 0.0, 0.0, 0.0, 1.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 0.0, 0.0, 0.0, 1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f, 0.0, 0.0, 0.0, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0, 0.0, 0.0, 0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f, 0.0, 0.0, 0.0, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 0.0, 0.0, 0.0, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 0.0, 0.0, 0.0, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 0.0, 0.0, 0.0, 1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f, 0.0, 0.0, 0.0, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 0.0, 0.0, 0.0, 0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, 0.0, 0.0, 0.0, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 0.0, 0.0, 0.0, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0, 0.0, 0.0, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0, 0.0, 0.0, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 0.0, 0.0, 0.0, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 0.0, 0.0, 0.0, 1.0f, 0.0f,

     0.5f,  0.5f,  0.5f, 0.0, 0.0, 0.0, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 0.0, 0.0, 0.0, 1.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 0.0, 0.0, 0.0, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 0.0, 0.0, 0.0, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 0.0, 0.0, 0.0, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 0.0, 0.0, 0.0, 1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 0.0, 0.0, 0.0, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 0.0, 0.0, 0.0, 1.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 0.0, 0.0, 0.0, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 0.0, 0.0, 0.0, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, 0.0, 0.0, 0.0, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0, 0.0, 0.0, 0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f, 0.0, 0.0, 0.0, 0.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 0.0, 0.0, 0.0, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 0.0, 0.0, 0.0, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 0.0, 0.0, 0.0, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 0.0, 0.0, 0.0, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 0.0, 0.0, 0.0, 0.0f, 1.0f
	};
  node->count = 36;
	glGenVertexArrays(1, &node->vao);
	glGenBuffers(1, &node->vbo);

	glBindBuffer(GL_ARRAY_BUFFER, node->vbo);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//
	glBindVertexArray(node->vao);
	//
	// glEnableVertexAttribArray(0);
	// glVertexAttribPointer(0, 8, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	//
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

#pragma GCC diagnostic pop

g_node* node3d_new()
{
	REF_NEW_AUTO_RELEASE(g_node3d, node)
	init_node(node);
	init_node3d(node);
	return node;
}

#ifdef __cplusplus
}
#endif
