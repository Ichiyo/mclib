#include <mstr/m_double_array.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"

void m_double_array_free(m_double_array* node)
{
  if(node->data) free(node->data);
	free(node);
}

/*EXPEND IMPLEMENTATION -- DO NOT DELETE THIS LINE*/


void m_double_array_push(m_double_array* arr, double number)
{
  arr->data = realloc(arr->data, (arr->length + 1) * sizeof(double));
  arr->data[arr->length] = number;
  arr->length++;
}

void m_double_array_remove(m_double_array* arr, long index)
{
  if(index >= 0 && index < arr->length)
  {
    if(index != arr->length - 1) memmove(arr->data+index, arr->data+index+1, (arr->length - index - 1) * sizeof(double));
    arr->length--;
  }
}

static m_double_array_func base_m_double_array_func =
{
  INHERIT_M_DOUBLE_ARRAY_FUNC
};

void m_double_array_init(m_double_array* node)
{
	node->func = &base_m_double_array_func;
  //TODO init
}

m_double_array* m_double_array_new()
{
	REF_NEW_AUTO_RELEASE(m_double_array, node)

  m_double_array_init(node);
	return node;
}

#pragma GCC diagnostic pop

#ifdef __cplusplus
}
#endif
