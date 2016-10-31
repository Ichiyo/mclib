#ifndef _M_IMAGE_H
#define _M_IMAGE_H

#include <base/ref.h>

#ifdef __cplusplus
extern "C" {
#endif

struct _g_image
{
  REF_MACRO
  int(*get_width)(void*);
  int(*get_height)(void*);
  void*(*get_pixels)(void*);
};
typedef struct _g_image g_image;

g_image* image_new_from_file(const char* file);

#ifdef __cplusplus
}
#endif

#endif
