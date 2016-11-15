#include <mstr/m_generic_array.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"

void m_generic_array_free(m_generic_array* node)
{
  if(node->data) free(node->data);
	free(node);
}

/*EXPEND IMPLEMENTATION -- DO NOT DELETE THIS LINE*/

static m_generic_array_func base_m_generic_array_func =
{
  INHERIT_M_GENERIC_ARRAY_FUNC
};

void m_generic_array_init(m_generic_array* node)
{
	node->func = &base_m_generic_array_func;
  //TODO init
}

m_generic_array* m_generic_array_new()
{
	REF_NEW_AUTO_RELEASE(m_generic_array, node)

  m_generic_array_init(node);
	return node;
}

#pragma GCC diagnostic pop

#ifdef __cplusplus
}
#endif
