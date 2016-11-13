#include <graphic/skin3d/m_skin_node.h>
#include <mstr/xml.h>
#include <utils/file_utils.h>

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

void m_skin_node_parse_collada_file(m_skin_node* node, char* path)
{

  parse_xml_file(path,

    SAFE_NEW_LAMBDA(void, (int depth, m_string* name, m_list* attributes)
    {
      printf("begin : %s\n",name->content);
      for(int i = 0; i < attributes->size; i += 2)
      {
        m_string* attr_name = (m_string*)attributes->func->get_index(attributes, i);
        m_string* attr_value = (m_string*)attributes->func->get_index(attributes, i + 1);
        printf("\t%s : %s\n",attr_name->content, attr_value->content);
      }
    },0),

    SAFE_NEW_LAMBDA(void, (int depth, m_string* content)
    {

    },0),

    SAFE_NEW_LAMBDA(void, (int depth, m_string* name)
    {
    },0)

  );
}

void m_skin_node_draw(m_skin_node* node)
{
  if(node->shader) node->shader->func->use(node->shader);
	else return;
	if(node->texture) node->texture->func->bind(node->texture, 0);
	else return;

  //TODO draw
}

void m_skin_node_set_shader(m_skin_node* arg_0, m_shader* arg_1)
{
	//TODO implement
}

void m_skin_node_set_texture(m_skin_node* arg_0, m_texture* arg_1)
{
	//TODO implement
}

static m_skin_node_func base_m_skin_node_func =
{
  INHERIT_M_SKIN_NODE_FUNC
};

void m_skin_node_init(m_skin_node* node)
{
	node->func = &base_m_skin_node_func;
  //TODO init
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
