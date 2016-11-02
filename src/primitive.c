#include <mstr/primitive.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

static void int_free(m_int* p)
{
  free(p);
}
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"

static ref_func base_int_func =
{
  BASE_REF_FUNC_INHERIT,
  .free = int_free
};

m_int* new_int(long value)
{
  REF_NEW_AUTO_RELEASE(m_int, ret);
  ret->func = &base_int_func;
  ret->data = value;
  return ret;
}
#pragma GCC diagnostic pop

#ifdef __cplusplus
}
#endif
