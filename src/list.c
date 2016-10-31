#include <mstr/list.h>
#include <stdlib.h>
#include <string.h>

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
static void* linked_list_first(m_list* list);

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

static void* linked_list_index(m_list* list, long index)
{
  m_list_linked_content* content = (m_list_linked_content*)list->content;
  if(index < list->size && index >= 0)
  {
    m_linked_list_node* node = content->first;
    while(index > 0)
    {
      node = node->right;
      index--;
    }
    return node->data;
  }
  else return 0;
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

static void* linked_list_first(m_list* list)
{
  m_list_linked_content* content = (m_list_linked_content*)list->content;
  if(content->first)
  {
    return content->first->data;
  }
  else return 0;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
m_list* linked_list_new()
{
  REF_NEW(m_list, ret)
  ret->auto_release(ret);
  ret->content = calloc(1, sizeof(m_list_linked_content));
  ret->free = linked_list_free;
  ret->push = linked_list_push;
  ret->pop = linked_list_pop;
  ret->get_last = linked_list_last;
  ret->get_first = linked_list_first;
  ret->get_index = linked_list_index;
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
  m_array_list_node** elements;
  long reserved;
};
typedef struct _m_array_list_content m_array_list_content;

static void array_list_free(m_list* list)
{
  m_array_list_content* content = (m_array_list_content*)list->content;
  while(list->size)
  {
    list->pop(list);
  }
  free(content->elements);
  free(content);
  free(list);
}

static void array_list_push(m_list* list, void* data, int is_ref)
{
  if(is_ref)
  {
    ((ref*)data)->retain(data);
  }
  m_array_list_node* node = calloc(1, sizeof(m_array_list_node));
  node->data = data;
  node->has_ref = is_ref;

  m_array_list_content* content = (m_array_list_content*)list->content;
  if(content->reserved == list->size)
  {
    content->reserved++;
    if(content->reserved == 1)
    {
      content->elements = calloc(1, sizeof(m_array_list_node*));
    }
    else
    {
      content->elements = realloc(content->elements, content->reserved*sizeof(m_array_list_node*));
    }
  }
  content->elements[list->size] = node;
  list->size++;
}

static void array_list_pop(m_list* list)
{
  m_array_list_content* content = (m_array_list_content*)list->content;
  if(list->size > 0)
  {
    m_array_list_node* last = content->elements[list->size-1];
    if(last->has_ref)
    {
      ((ref*)last->data)->release(last->data);
    }
    free(last);
    list->size--;
  }
}

static void* array_list_index(m_list* list, long index)
{
  m_array_list_content* content = (m_array_list_content*)list->content;
  if(index >= 0 && index < list->size) return content->elements[index]->data;
  else return 0;
}

static void* array_list_last(m_list* list)
{
  m_array_list_content* content = (m_array_list_content*)list->content;
  if(list->size > 0) return content->elements[list->size-1]->data;
  else return 0;
}

static void* array_list_first(m_list* list)
{
  m_array_list_content* content = (m_array_list_content*)list->content;
  if(list->size > 0) return content->elements[0]->data;
  else return 0;
}

static void array_list_remove(m_list* list, void* data)
{
  m_array_list_content* content = (m_array_list_content*)list->content;
  for(unsigned int i = 0; i < list->size; i++)
  {
    if(content->elements[i]->data == data)
    {
      m_array_list_node* node = content->elements[i];
      if(node->has_ref)
      {
        ((ref*)node->data)->release(node->data);
      }
      free(node);

      memmove(content->elements+i, content->elements+i+1, (list->size - i - 1) * sizeof(m_array_list_node*));
      list->size--;
      break;
    }
  }
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
m_list* array_list_new()
{
  REF_NEW(m_list, ret)
  ret->auto_release(ret);
  ret->content = calloc(1, sizeof(m_array_list_content));
  ret->free = array_list_free;
  ret->push = array_list_push;
  ret->pop = array_list_pop;
  ret->get_last = array_list_last;
  ret->get_first = array_list_first;
  ret->get_index = array_list_index;
  ret->remove = array_list_remove;
  return ret;
}
#pragma GCC diagnostic pop

#ifdef __cplusplus
}
#endif
