#include <graphic/image.h>
#include <stdlib.h>

#ifdef linux
  #if defined(USE_SDL)
  #include <SDL2/SDL.h>
  #include <SDL2/SDL_image.h>
  #endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if defined(USE_SDL)

struct _sdl_image
{
  CONSTRUCT_REF(g_image_func)
  SDL_Surface* _image;
};
typedef struct _sdl_image sdl_image;

static void free_image(sdl_image* image)
{
  if(image->_image)
  {
    SDL_FreeSurface(image->_image);
  }
  free(image);
}

static void init_image(sdl_image* image, const char* file)
{
  image->_image = IMG_Load(file);
}

static int image_get_width(sdl_image* image)
{
  if(image->_image) return image->_image->w;
  else return 0;
}

static int image_get_height(sdl_image* image)
{
  if(image->_image) return image->_image->h;
  else return 0;
}

static void* image_get_pixels(sdl_image* image)
{
  if(image->_image) return image->_image->pixels;
  else return 0;
}
#endif

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"

static g_image_func base_g_image_func =
{
    BASE_REF_FUNC_INHERIT,
    .free = free_image,
    .get_width = image_get_width,
    .get_height = image_get_height,
    .get_pixels = image_get_pixels
};

g_image* image_new_from_file(const char* file)
{
  g_image* ret = 0;

  #if defined(USE_SDL)
  REF_NEW_AUTO_RELEASE(sdl_image, image)
  init_image(image, file);
  image->func = &base_g_image_func;
  ret = (g_image*)image;
  #endif

  return ret;
}
#pragma GCC diagnostic pop

#ifdef __cplusplus
}
#endif
