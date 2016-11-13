#include <mstr/m_int_array.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"

void m_int_array_free(m_int_array* node)
{
  if(node->data) free(node->data);
	free(node);
}

/*EXPEND IMPLEMENTATION -- DO NOT DELETE THIS LINE*/


void m_int_array_push(m_int_array* arr, int number)
{
  arr->data = realloc(arr->data, (arr->length + 1) * sizeof(int));
  arr->data[arr->length] = number;
  arr->length++;
}

void m_int_array_remove(m_int_array* arr, long index)
{
  if(index >= 0 && index < arr->length)
  {
    if(index != arr->length - 1) memmove(arr->data+index, arr->data+index+1, (arr->length - index - 1) * sizeof(int));
    arr->length--;
  }
}

static m_int_array_func base_m_int_array_func =
{
  INHERIT_M_INT_ARRAY_FUNC
};

void m_int_array_init(m_int_array* node)
{
	node->func = &base_m_int_array_func;
  //TODO init
}

m_int_array* m_int_array_new()
{
	REF_NEW_AUTO_RELEASE(m_int_array, node)

  m_int_array_init(node);
	return node;
}

#pragma GCC diagnostic pop

#ifdef __cplusplus
}
#endif
