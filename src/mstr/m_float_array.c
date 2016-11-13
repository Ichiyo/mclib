#include <mstr/m_float_array.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"

void m_float_array_free(m_float_array* node)
{
  if(node->data) free(node->data);
	free(node);
}

/*EXPEND IMPLEMENTATION -- DO NOT DELETE THIS LINE*/


void m_float_array_push(m_float_array* arr, float number)
{
	arr->data = realloc(arr->data, (arr->length + 1) * sizeof(float));
  arr->data[arr->length] = number;
  arr->length++;
}

void m_float_array_remove(m_float_array* arr, long index)
{
	if(index >= 0 && index < arr->length)
  {
    if(index != arr->length - 1) memmove(arr->data+index, arr->data+index+1, (arr->length - index - 1) * sizeof(float));
    arr->length--;
  }
}

static m_float_array_func base_m_float_array_func =
{
  INHERIT_M_FLOAT_ARRAY_FUNC
};

void m_float_array_init(m_float_array* node)
{
	node->func = &base_m_float_array_func;
}

m_float_array* m_float_array_new()
{
	REF_NEW_AUTO_RELEASE(m_float_array, node)

  m_float_array_init(node);
	return node;
}

#pragma GCC diagnostic pop

#ifdef __cplusplus
}
#endif
