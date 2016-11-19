#include <graphic/skin3d/m_skin_node.h>
#include <mstr/xml.h>
#include <utils/file_utils.h>
#include <graphic/skin3d/m_geometry_mesh.h>
#include <graphic/skin3d/m_controller_skin.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"

void m_skin_node_free(m_skin_node* node)
{
  QUICK_RELEASE(node->shader);
  QUICK_RELEASE(node->texture);
  QUICK_RELEASE(node->join);
  if(node->vbo) glDeleteBuffers(1, &node->vbo);
  if(node->vao) glDeleteVertexArrays(1, &node->vao);
	m_node_free(node);
}

/*EXPEND IMPLEMENTATION -- DO NOT DELETE THIS LINE*/

void m_skin_node_visit(m_skin_node* node, m_matrix4 current_model, int flag)
{
  if(!node->visible) return;

	flag = flag | node->transform_dirty;
	if(flag)
	{
		m_matrix4 model = matrix4_identity;
		model = matrix4_translate_vector3(model, node->position);
    model = matrix4_mul(model,node->fix_model);
		model = matrix4_mul(model,matrix4_create_quaternion(node->quat));
		model = matrix4_scale_vector3(model, node->scale);
    node->render_model = model;
    node->render_model = matrix4_mul(current_model, node->render_model);
    node->render_model = matrix4_scale_vector3(node->render_model, node->size);
    model= matrix4_translate_vector3(model, vector3_new(-node->anchor.v[0] * node->size.v[0], -node->anchor.v[1] * node->size.v[1], -node->anchor.v[2] * node->size.v[2]));
		model = matrix4_mul(current_model, model);
    node->model = model;
		node->transform_dirty = 0;
	}

	if(node->func->draw) node->func->draw(node);
	if(node->children)
	{
		long size = node->children->size;
		for(long i = 0; i < size; i++)
		{
			m_node* child = (m_node*)node->children->func->get_index(node->children, i);
			child->func->visit(child, node->model, flag);
		}
	}
}

void m_skin_node_build_skin(m_skin_node* node, m_controller_skin* skin)
{
	node->bind_shape_matrix = skin->bind_shape_matrix;
  m_float_array* positions = 0;
  m_float_array* normals = 0;
  m_float_array* uvs = 0;

  m_geometry_mesh* mesh = skin->mesh;
  m_mesh_polylist* polylist = mesh->polylist;
  for(long i = 0; i < mesh->polylist->sources->size; i++)
  {
    m_mesh_source* source = _(mesh->polylist->sources, get_index, i);
    m_string* semantic = _(mesh->polylist->semantics, get_index, i);
    if(strcmp(semantic->content, "VERTEX") == 0) positions = source->farr;
    if(strcmp(semantic->content, "NORMAL") == 0) normals = source->farr;
    if(strcmp(semantic->content, "TEXCOORD") == 0) uvs = source->farr;
  }

  m_float_array* vertex_join_ids = m_float_array_new();
  m_float_array* vertex_weights = m_float_array_new();

  int v_index = 0;

  for(long i = 0; i < skin->vcount->length; i++)
  {
    int c = GENERIC_ARRAY_GET(skin->vcount, int, i);
    if(c == 0)
    {
      // expand zero weights due to requirement from shader
      for(int j = 0; j < skin->max_vcount; j++)
      {
        _(vertex_join_ids, push, 0.0);
        if(j == 0) _(vertex_weights, push, 1.0);
        else _(vertex_weights, push, 0.0);
      }
    }
    else
    {

      for(int j = 0; j < c; j++)
      {
        if(v_index < skin->v->length)
        {
          int join_index = GENERIC_ARRAY_GET(skin->v, int, v_index);
          v_index++;
          int weight_index = GENERIC_ARRAY_GET(skin->v, int, v_index);
          v_index++;

          _(vertex_join_ids, push, (float)join_index);
          float weight = GENERIC_ARRAY_GET(skin->weights, float, weight_index);
          _(vertex_weights, push, weight);
        }
        else
        {
          // error ???
          _(vertex_join_ids, push, 0.0);
          if(j == 0) _(vertex_weights, push, 1.0);
          else _(vertex_weights, push, 0.0);
        }
      }
      if(c > 0 && c < skin->max_vcount)
      {
        // expand zero weights due to requirement from shader
        for(int j = c; j < skin->max_vcount; j++)
        {
          _(vertex_join_ids, push, 0.0);
          _(vertex_weights, push, 0.0);
        }
      }
    }
  }


  GLfloat* realvertices = 0;
  long total_size = 0;
  int one_vertex_size = 0;

  if(uvs)
  {
    node->has_uvs = 1;
    // 3 vertex + 3 normal + 2 texcoord + max_vcount joins_id + max_vcount weights
    one_vertex_size = 3 + 3 + 2 + 2 * skin->max_vcount;
    node->vertices_count = polylist->p->length / 3;
    total_size = (polylist->p->length / 3)* one_vertex_size * sizeof(GLfloat);
    realvertices = malloc(total_size);
    int index = 0;
    int vertices_id = 0;

    for(long i = 0; i < polylist->p->length; i+= 3, index++)
    {
      int vertex_id = polylist->p->data[i];
      int normal_id = polylist->p->data[i+1];
      int uv_id = polylist->p->data[i+2];

      realvertices[vertices_id++] = positions->data[vertex_id * 3];
      realvertices[vertices_id++] = positions->data[vertex_id * 3 + 1];
      realvertices[vertices_id++] = positions->data[vertex_id * 3 + 2];
      realvertices[vertices_id++] = normals->data[normal_id * 3];
      realvertices[vertices_id++] = normals->data[normal_id * 3 + 2];
      realvertices[vertices_id++] = -normals->data[normal_id * 3 + 1];
      realvertices[vertices_id++] = uvs->data[uv_id * 2];
      realvertices[vertices_id++] = uvs->data[uv_id * 2 + 1];

      for(long j = 0; j < skin->max_vcount; j++)
      {
        realvertices[vertices_id++] = vertex_join_ids->data[vertex_id * skin->max_vcount + j];
        realvertices[vertices_id++] = vertex_weights->data[vertex_id * skin->max_vcount + j];
      }
    }
  }
  else
  {
    // 3 vertex + 3 normal + max_vcount joins_id + max_vcount weights
    one_vertex_size = 3 + 3 + 2 * skin->max_vcount;
    node->vertices_count = polylist->p->length / 2;
    total_size = (polylist->p->length / 2)* one_vertex_size * sizeof(GLfloat);
    realvertices = malloc(total_size);
    int index = 0;
    int vertices_id = 0;
    for(long i = 0; i < polylist->p->length; i+= 2, index++)
    {
      int vertex_id = polylist->p->data[i];
      int normal_id = polylist->p->data[i+1];

      realvertices[vertices_id++] = positions->data[vertex_id * 3];
      realvertices[vertices_id++] = positions->data[vertex_id * 3 + 1];
      realvertices[vertices_id++] = positions->data[vertex_id * 3 + 2];
      realvertices[vertices_id++] = normals->data[normal_id * 3];
      realvertices[vertices_id++] = normals->data[normal_id * 3 + 2];
      realvertices[vertices_id++] = -normals->data[normal_id * 3 + 1];

      for(long j = 0; j < skin->max_vcount; j++)
      {
        realvertices[vertices_id++] = vertex_join_ids->data[vertex_id * skin->max_vcount + j];
        realvertices[vertices_id++] = vertex_weights->data[vertex_id * skin->max_vcount + j];
      }
    }
  }

  glBindBuffer(GL_ARRAY_BUFFER, node->vbo);
  glBufferData(GL_ARRAY_BUFFER, total_size, realvertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
	free(realvertices);

  m_string* _3d_vert = read_string_from_file("res/shaders/shader_skin_3d.vert");
  m_string* _3d_frag = read_string_from_file("res/shaders/shader_skin_3d.frag");

  char i_to_s[10];
  snprintf(i_to_s, sizeof(i_to_s), "%d", skin->max_vcount);
  _3d_vert->func->replace_str(_3d_vert, new_string_from_char("$number_join_ids"), new_string_from_char(i_to_s));
  snprintf(i_to_s, sizeof(i_to_s), "%d", skin->join_names->size);
  _3d_vert->func->replace_str(_3d_vert, new_string_from_char("$number_joins"), new_string_from_char(i_to_s));
  _3d_vert->func->replace_str(_3d_vert, new_string_from_char("$use_model_index"), new_string_from_char("0"));
  snprintf(i_to_s, sizeof(i_to_s), "%d", uvs ? 1 : 0);
  _3d_vert->func->replace_str(_3d_vert, new_string_from_char("$has_texture"), new_string_from_char(i_to_s));
  _3d_frag->func->replace_str(_3d_frag, new_string_from_char("$has_texture"), new_string_from_char(i_to_s));
  m_shader* shader = m_shader_new_from_source(_3d_vert->content, _3d_frag->content);
  QUICK_RELEASE(_3d_vert);
  QUICK_RELEASE(_3d_frag);

  QUICK_RELEASE(node->shader);
  node->shader = shader;
  QUICK_RETAIN(node->shader);

  node->shader->func->use(node->shader);


  glBindVertexArray(node->vao);
	glBindBuffer(GL_ARRAY_BUFFER, node->vbo);
  GLint posAttrib = glGetAttribLocation(shader->func->get_id(shader), "position");
  glEnableVertexAttribArray(posAttrib);
  glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, one_vertex_size * sizeof(GLfloat), 0);

  GLint norAttrib = glGetAttribLocation(shader->func->get_id(shader), "normal");
  glEnableVertexAttribArray(norAttrib);
  glVertexAttribPointer(norAttrib, 3, GL_FLOAT, GL_FALSE, one_vertex_size * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
  if(uvs)
  {
    GLint texAttrib = glGetAttribLocation(shader->func->get_id(shader), "texcoord");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, one_vertex_size * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
  }

  int offset = uvs ? 8 : 6;
  for(int i = 0; i < skin->max_vcount; i++)
  {
    char id[15];
    snprintf(id, sizeof(id), "%d", i);
    m_string* join_attr_name = new_string_from_char("joinIds_");
    m_string* weight_attr_name = new_string_from_char("weights_");
    _(join_attr_name,cat_char,id);
    _(weight_attr_name,cat_char,id);

    GLint joinIdAttrib = glGetAttribLocation(shader->func->get_id(shader), join_attr_name->content);
    glEnableVertexAttribArray(joinIdAttrib);
    glVertexAttribPointer(joinIdAttrib, 1, GL_FLOAT, GL_FALSE, one_vertex_size * sizeof(GLfloat), (void*)(offset * sizeof(GLfloat)));
    offset++;
    GLint weightAttrib = glGetAttribLocation(shader->func->get_id(shader), weight_attr_name->content);
    glEnableVertexAttribArray(weightAttrib);
    glVertexAttribPointer(weightAttrib, 1, GL_FLOAT, GL_FALSE, one_vertex_size * sizeof(GLfloat), (void*)(offset * sizeof(GLfloat)));
    offset++;
  }

	glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void m_skin_node_build_mesh(m_skin_node* node, m_geometry_mesh* mesh)
{
  m_float_array* positions = 0;
  m_float_array* normals = 0;
  m_float_array* uvs = 0;

  m_mesh_polylist* polylist = mesh->polylist;
  for(long i = 0; i < mesh->polylist->sources->size; i++)
  {
    m_mesh_source* source = _(mesh->polylist->sources, get_index, i);
    m_string* semantic = _(mesh->polylist->semantics, get_index, i);
    if(strcmp(semantic->content, "VERTEX") == 0) positions = source->farr;
    if(strcmp(semantic->content, "NORMAL") == 0) normals = source->farr;
    if(strcmp(semantic->content, "TEXCOORD") == 0) uvs = source->farr;
  }

  GLfloat* realvertices = 0;
  long total_size = 0;
  int one_vertex_size = 0;

  if(uvs)
  {
    // 3 vertex + 3 normal + 2 texcoord
    one_vertex_size = 3 + 3 + 2;
    node->vertices_count = polylist->p->length / 3;
    total_size = (polylist->p->length / 3)* one_vertex_size * sizeof(GLfloat);
    realvertices = malloc(total_size);
    int index = 0;
    int vertices_id = 0;

    for(long i = 0; i < polylist->p->length; i+= 3, index++)
    {
      int vertex_id = polylist->p->data[i];
      int normal_id = polylist->p->data[i+1];
      int uv_id = polylist->p->data[i+2];

      realvertices[vertices_id++] = positions->data[vertex_id * 3];
      realvertices[vertices_id++] = positions->data[vertex_id * 3 + 1];
      realvertices[vertices_id++] = positions->data[vertex_id * 3 + 2];
      realvertices[vertices_id++] = normals->data[normal_id * 3];
      realvertices[vertices_id++] = normals->data[normal_id * 3 + 1];
      realvertices[vertices_id++] = normals->data[normal_id * 3 + 2];
      realvertices[vertices_id++] = uvs->data[uv_id * 2];
      realvertices[vertices_id++] = uvs->data[uv_id * 2 + 1];
    }
  }
  else
  {
    // 3 vertex + 3 normal + max_vcount joins_id + max_vcount weights
    one_vertex_size = 3 + 3;
    node->vertices_count = polylist->p->length / 2;
    total_size = (polylist->p->length / 2)* one_vertex_size * sizeof(GLfloat);
    realvertices = malloc(total_size);
    int index = 0;
    int vertices_id = 0;
    for(long i = 0; i < polylist->p->length; i+= 2, index++)
    {
      int vertex_id = polylist->p->data[i];
      int normal_id = polylist->p->data[i+1];

      realvertices[vertices_id++] = positions->data[vertex_id * 3];
      realvertices[vertices_id++] = positions->data[vertex_id * 3 + 1];
      realvertices[vertices_id++] = positions->data[vertex_id * 3 + 2];
      realvertices[vertices_id++] = normals->data[normal_id * 3];
      realvertices[vertices_id++] = normals->data[normal_id * 3 + 1];
      realvertices[vertices_id++] = normals->data[normal_id * 3 + 2];
    }
  }

  glBindBuffer(GL_ARRAY_BUFFER, node->vbo);
  glBufferData(GL_ARRAY_BUFFER, total_size, realvertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
	free(realvertices);

  m_string* _3d_vert = read_string_from_file("res/shaders/shader_skin_3d.vert");
  m_string* _3d_frag = read_string_from_file("res/shaders/shader_skin_3d.frag");

  char i_to_s[10];
  _3d_vert->func->replace_str(_3d_vert, new_string_from_char("$number_join_ids"), new_string_from_char("0"));
  _3d_vert->func->replace_str(_3d_vert, new_string_from_char("$number_joins"), new_string_from_char("0"));
  _3d_vert->func->replace_str(_3d_vert, new_string_from_char("$use_model_index"), new_string_from_char("0"));
  snprintf(i_to_s, sizeof(i_to_s), "%d", uvs ? 1 : 0);
  _3d_vert->func->replace_str(_3d_vert, new_string_from_char("$has_texture"), new_string_from_char(i_to_s));
  _3d_frag->func->replace_str(_3d_frag, new_string_from_char("$has_texture"), new_string_from_char(i_to_s));
  m_shader* shader = m_shader_new_from_source(_3d_vert->content, _3d_frag->content);
  QUICK_RELEASE(_3d_vert);
  QUICK_RELEASE(_3d_frag);

  QUICK_RELEASE(node->shader);
  node->shader = shader;
  QUICK_RETAIN(node->shader);

  node->shader->func->use(node->shader);


  glBindVertexArray(node->vao);

	glBindBuffer(GL_ARRAY_BUFFER, node->vbo);
  GLint posAttrib = glGetAttribLocation(shader->func->get_id(shader), "position");
  glEnableVertexAttribArray(posAttrib);
  glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, one_vertex_size * sizeof(GLfloat), 0);

  GLint norAttrib = glGetAttribLocation(shader->func->get_id(shader), "normal");
  glEnableVertexAttribArray(norAttrib);
  glVertexAttribPointer(norAttrib, 3, GL_FLOAT, GL_FALSE, one_vertex_size * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
  if(uvs)
  {
    GLint texAttrib = glGetAttribLocation(shader->func->get_id(shader), "texcoord");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, one_vertex_size * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
  }

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void m_skin_node_set_join(m_skin_node* node, m_skin_join* join)
{
	QUICK_RELEASE(node->join);
  node->join = join;
  QUICK_RETAIN(node->join);
}
float t = 0;
void m_skin_node_update_skeleton(m_skin_node* node, m_skin_join* join)
{
  if(join->parent)
  {
    m_skin_join* parent = join->parent->owner;

    join->world_matrix = matrix4_identity;
    join->world_matrix = parent->world_matrix;
    join->world_matrix = matrix4_mul(join->world_matrix, join->bind_pose);
  }
  else
  {
    join->world_matrix = join->bind_pose;
  }
  if(strcmp(join->sid->content, "Bone_003") == 0)
  {
    quaternion offset_q = quaternion_new_angle_axis(DEG_TO_RAD(t * 0.1f), 1, 0, 0);
    m_matrix4 m = matrix4_create_quaternion(offset_q);
    join->world_matrix = matrix4_mul(join->world_matrix, m);
  }

  t+= 1;

  join->final_matrix = join->world_matrix;
  join->final_matrix = matrix4_mul(join->final_matrix, join->inverse_bind_pose);
  join->final_matrix = matrix4_mul(node->bind_shape_matrix, join->final_matrix);

  GLint uniform = glGetUniformLocation(node->shader->func->get_id(node->shader), join->uniform_id->content);
  glUniformMatrix4fv(uniform, 1, GL_FALSE, join->final_matrix.m);

  for(long i = 0; i < join->children->size; i++)
  {
    m_skin_join* child = _(join->children, get_index, i);
    _(node, update_skeleton, child);
  }
}

void m_skin_node_draw(m_skin_node* node)
{
  if(node->shader) node->shader->func->use(node->shader);
	else return;

  if(node->has_uvs)
  {
    if(node->texture) node->texture->func->bind(node->texture, 0);
    else return;
  }

  GLint uniModel = glGetUniformLocation(node->shader->func->get_id(node->shader), "model");
	glUniformMatrix4fv(uniModel, 1, GL_FALSE, node->render_model.m);

  // upload skeleton
  if(node->join) _(node, update_skeleton, node->join);

	glBindVertexArray(node->vao);
	glDrawArrays(GL_TRIANGLES, 0, node->vertices_count);
	glBindVertexArray(0);
}

void m_skin_node_set_shader(m_skin_node* arg_0, m_shader* arg_1)
{
  // not used
  // join->bind_pose  = matrix4_mul(m, join->bind_pose);
}

void m_skin_node_set_texture(m_skin_node* node, m_texture* texture)
{
    if(node->texture) node->texture->func->release(node->texture);
    node->texture = texture;
    if(node->texture) node->texture->func->retain(node->texture);
}

static m_skin_node_func base_m_skin_node_func =
{
  INHERIT_M_SKIN_NODE_FUNC
};

void m_skin_node_init(m_skin_node* node)
{
	node->func = &base_m_skin_node_func;
  node->bind_shape_matrix = matrix4_identity;

  node->vertices_count = 0;
	glGenVertexArrays(1, &node->vao);
	glGenBuffers(1, &node->vbo);

	glBindBuffer(GL_ARRAY_BUFFER, node->vbo);
	glBindVertexArray(node->vao);
	//
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

m_skin_node* m_skin_node_new()
{
	REF_NEW_AUTO_RELEASE(m_skin_node, node)
  m_node_init(node);
  m_skin_node_init(node);
	return node;
}

#pragma GCC diagnostic pop

#ifdef __cplusplus
}
#endif
