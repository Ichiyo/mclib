#include <graphic/image.h>
#include <graphic/graphic.h>
#include <stdlib.h>

#ifdef linux
  #if defined(USE_SDL)
  #include <SDL2/SDL.h>
  #include <SDL2/SDL_image.h>
  #endif
#else
  #if defined(USE_SDL)
  #include <SDL2/SDL.h>
  #include <SDL2/SDL_image.h>
  #endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if defined(USE_SDL)

EXTEND_REF(sdl_image, g_image_func,
  SDL_Surface* _image;
  int _type;
);

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

  /* Extracting color components from a 32-bit color value */
  SDL_PixelFormat *fmt;
  SDL_Surface *surface = image->_image;
  Uint32 temp, pixel;
  Uint8 red, green, blue, alpha;

  fmt = surface->format;
  SDL_LockSurface(surface);
  pixel = *((Uint32*)surface->pixels);
  SDL_UnlockSurface(surface);

  /* Get Red component */
  temp = pixel & fmt->Rmask;  /* Isolate red component */
  temp = temp >> fmt->Rshift; /* Shift it down to 8-bit */
  temp = temp << fmt->Rloss;  /* Expand to a full 8-bit number */
  red = (Uint8)temp;

  /* Get Green component */
  temp = pixel & fmt->Gmask;  /* Isolate green component */
  temp = temp >> fmt->Gshift; /* Shift it down to 8-bit */
  temp = temp << fmt->Gloss;  /* Expand to a full 8-bit number */
  green = (Uint8)temp;

  /* Get Blue component */
  temp = pixel & fmt->Bmask;  /* Isolate blue component */
  temp = temp >> fmt->Bshift; /* Shift it down to 8-bit */
  temp = temp << fmt->Bloss;  /* Expand to a full 8-bit number */
  blue = (Uint8)temp;

  /* Get Alpha component */
  temp = pixel & fmt->Amask;  /* Isolate alpha component */
  temp = temp >> fmt->Ashift; /* Shift it down to 8-bit */
  temp = temp << fmt->Aloss;  /* Expand to a full 8-bit number */
  alpha = (Uint8)temp;

  if(alpha == 0)
  {
    image->_type = GL_RGB;
  }
  else
  {
    image->_type = GL_RGBA;
  }

}

static int image_get_type(sdl_image* image)
{
  if(image->_image) return image->_type;
  else return -1;
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
    .get_pixels = image_get_pixels,
    .get_type = image_get_type
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
