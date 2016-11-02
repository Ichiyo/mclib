#ifndef _M_IMAGE_H
#define _M_IMAGE_H

#include <base/ref.h>

#ifdef __cplusplus
extern "C" {
#endif

EXTEND_REF_FUNC(g_image_func,
  int(*get_width)(void*);
  int(*get_height)(void*);
  void*(*get_pixels)(void*);
  int(*get_type)(void*);
);

EXTEND_REF(g_image, g_image_func,);

g_image* image_new_from_file(const char* file);

#ifdef __cplusplus
}
#endif

#endif
