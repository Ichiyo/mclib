#include <mstr/list.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

struct _m_linked_list_node
{
  void* data;
  int has_ref;
  struct _m_linked_list_node* left;
  struct _m_linked_list_node* right;
};
typedef struct _m_linked_list_node m_linked_list_node;

struct _m_list_linked_content
{
  m_linked_list_node* first;
  m_linked_list_node* last;
};
typedef struct _m_list_linked_content m_list_linked_content;

static void linked_list_pop(m_list* list);
static void linked_list_free(m_list* list);
static void linked_list_remove_node(m_list* list, m_linked_list_node* node);
static void linked_list_push(m_list* list, void* data, int is_ref);
static void linked_list_remove(m_list* list, void* data);
static void* linked_list_last(m_list* list);

static void linked_list_free(m_list* list)
{
  m_list_linked_content* content = (m_list_linked_content*)list->content;
  while(content->first)
  {
    linked_list_pop(list);
  }
  free(content);
  free(list);
}

static void linked_list_remove_node(m_list* list, m_linked_list_node* node)
{
  m_list_linked_content* content = (m_list_linked_content*)list->content;
  list->size--;
  m_linked_list_node* left = node->left;
  m_linked_list_node* right = node->right;
  if(node == content->last)
  {
    left->right = 0;
    content->last = left;
    if(content->last == content->first) content->last = 0;
  }
  else if(node == content->first)
  {
    if(right)
    {
      right->left = 0;
    }
    content->first = right;
    if(content->first == content->last) content->last = 0;
  }
  else
  {
    left->right = right;
    right->left = left;
  }
  if(node->has_ref)
  {
    ((ref*)node->data)->release(node->data);
  }
  free(node);
}

static void linked_list_push(m_list* list, void* data, int is_ref)
{
  m_list_linked_content* content = (m_list_linked_content*)list->content;
  list->size++;
  if(is_ref)
  {
    ((ref*)data)->retain(data);
  }
  m_linked_list_node* node = calloc(1, sizeof(m_linked_list_node));
  node->data = data;
  node->has_ref = is_ref;

  if(!content->first)
  {
    content->first = node;
  }
  else
  {
    if(!content->last)
    {
      content->last = node;
      content->first->right = node;
      content->last->left = content->first;
    }
    else
    {
      content->last->right = node;
      node->left = content->last;
      content->last = node;
    }
  }
}

static void linked_list_remove(m_list* list, void* data)
{
  m_list_linked_content* content = (m_list_linked_content*)list->content;
  m_linked_list_node* node = content->first;
  while(node)
  {
    if(node->data == data)
    {
      linked_list_remove_node(list, node);
      break;
    }
    node = node->right;
  }
}

static void linked_list_pop(m_list* list)
{
  m_list_linked_content* content = (m_list_linked_content*)list->content;
  if(content->last)
  {
    linked_list_remove_node(list, content->last);
  }
  else if(content->first)
  {
    linked_list_remove_node(list, content->first);
  }
}

static void* linked_list_last(m_list* list)
{
  m_list_linked_content* content = (m_list_linked_content*)list->content;
  if(content->last)
  {
    return content->last->data;
  }
  else if(content->first)
  {
    return content->first->data;
  }
  else return 0;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
m_list* linked_list_new()
{
  m_list* ret = calloc(1, sizeof(m_list));
  ref_init(ret);
  ret->auto_release(ret);
  ret->content = calloc(1, sizeof(m_list_linked_content));
  ret->free = linked_list_free;
  ret->push = linked_list_push;
  ret->pop = linked_list_pop;
  ret->get_last = linked_list_last;
  ret->remove = linked_list_remove;
  return ret;
}
#pragma GCC diagnostic pop

//-----------------------------------------------------
// array list
//-----------------------------------------------------

struct _m_array_list_node
{
  void* data;
  int has_ref;
};
typedef struct _m_array_list_node m_array_list_node;

struct _m_array_list_content
{
  m_array_list_content* elements;
  int ordered;
};
typedef struct _m_array_list_content m_array_list_content;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
m_list* array_list_new()
{
  m_list* ret = calloc(1, sizeof(m_list));
  ref_init(ret);
  ret->auto_release(ret);
  ret->content = calloc(1, sizeof(m_list_linked_content));
  ret->free = linked_list_free;
  ret->push = linked_list_push;
  ret->pop = linked_list_pop;
  ret->get_last = linked_list_last;
  ret->remove = linked_list_remove;
  return ret;
}
#pragma GCC diagnostic pop

#ifdef __cplusplus
}
#endif
