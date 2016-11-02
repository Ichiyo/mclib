#include <mstr/data.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

static void free_data(m_data* d)
{
  if(d->bytes) free(d->bytes);
  free(d);
}

static void data_put(m_data* des, char* src, long count)
{
  des->bytes = realloc(des->bytes, (des->size + count) * sizeof(char));
  memcpy(des->bytes + des->size, src, count);
  des->size = des->size + count;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"

static m_data_func base_m_data_func =
{
  BASE_REF_FUNC_INHERIT,
  .free = free_data,
  .put = data_put
};

m_data* data_new()
{
  REF_NEW_AUTO_RELEASE(m_data, d)
  d->func = &base_m_data_func;
  return d;
}
#pragma GCC diagnostic pop

#ifdef __cplusplus
}
#endif
