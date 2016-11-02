#include <graphic/texture.h>
#include <graphic/graphic.h>
#include <mstr/map.h>
#include <string.h>
#include <mstr/list.h>

#ifdef __cplusplus
extern "C" {
#endif

struct _opengl_texture
{
  CONSTRUCT_REF(g_texture_func)
  GLuint id;
};
typedef struct _opengl_texture opengl_texture;

static void free_texture(opengl_texture* tex)
{
  if(tex->id)
  {
    glDeleteTextures(1, &tex->id);
  }
  free(tex);
}

static void init_texture(opengl_texture* tex, g_image* image)
{
  glGenTextures(1, &tex->id);
  glBindTexture(GL_TEXTURE_2D, tex->id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->func->get_width(image), image->func->get_height(image), 0, GL_RGBA, GL_UNSIGNED_BYTE, image->func->get_pixels(image));
  glGenerateMipmap(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 0);
}

static void texture_bind(opengl_texture* tex)
{
  if(tex->id)
  {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex->id);
  }
}

//-----------------------------------------------------

struct _texture_cache_value
{
  CONSTRUCT_REF(ref_func)
  m_string* name;
  weak_ref* texture_ref;
};
typedef struct _texture_cache_value texture_cache_value;

static void texture_cache_value_free(texture_cache_value* value)
{
  if(value->name)
  {
    value->name->func->release(value->name);
  }
  if(value->texture_ref)
  {
    value->texture_ref->func->release(value->texture_ref);
  }
  free(value);
}

static ref_func texture_cache_value_func =
{
  BASE_REF_FUNC_INHERIT,
  .free = texture_cache_value_free
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
texture_cache_value* new_texture_cache_value()
{
  REF_NEW_AUTO_RELEASE(texture_cache_value, ret)
  ret->func = &texture_cache_value_func;
  return ret;
}
#pragma GCC diagnostic pop

//--------------------------------------------------------------
static m_map* texture_cache = 0;

static unsigned long hash_string_to_int(const char* str, long length)
{
  unsigned long mod = 0;
  for(long i = 0; i < length; i++)
  {
    mod = (mod * 32 + str[i]) % 100;
  }
  return mod;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"

static g_texture_func base_g_texture_func =
{
  BASE_REF_FUNC_INHERIT,
  .free = free_texture,
  .bind = texture_bind
};

g_texture* texture_new_from_image(g_image* image)
{
  REF_NEW_AUTO_RELEASE(opengl_texture, ret)
  init_texture(ret, image);
  ret->func = &base_g_texture_func;
  return ret;
}

static g_texture* texture_new_from_file_char_length(const char* path, long length)
{
  if(!texture_cache)
  {
    texture_cache = create_map();
    texture_cache->func->retain(texture_cache);
  }

  unsigned long key = hash_string_to_int(path, length);
  m_list* list = (m_list*)texture_cache->func->get(texture_cache, key);
  if(list)
  {
    for(long i = 0; i < list->size; i++)
    {
      texture_cache_value* value = list->func->get_index(list, i);
      if(strcmp(value->name->content, path) == 0)
      {
        if(value->texture_ref->valid)
        {
          // found
          return (g_texture*)value->texture_ref->owner;
        }
        else
        {
          // texture created from path no longer exists
          list->func->remove(list, value);
        }
        break;
      }
    }
  }
  else
  {
    g_image* image = image_new_from_file(path);
    g_texture* tex = texture_new_from_image(image);
    image->func->release(image);

    m_list* list = linked_list_new();
    texture_cache->func->insert(texture_cache, key, list, 1);

    texture_cache_value* val = new_texture_cache_value();
    val->name = new_string();
    val->name->func->cat_char(val->name, (char*)path);
    val->name->func->retain(val->name);
    val->texture_ref = tex->func->new_weak_ref(tex);
    val->texture_ref->func->retain(val->texture_ref);

    list->func->push(list, val, 1);

    return tex;
  }
}

g_texture* texture_new_from_file_char(const char* path)
{
  return texture_new_from_file_char_length(path, strlen(path));
}

g_texture* texture_new_from_file_string(m_string* file)
{
  return texture_new_from_file_char_length(file->content, file->length);
}

void texture_free_cache()
{
  if(texture_cache)
  {
    texture_cache->func->release(texture_cache);
  }
  texture_cache = 0;
}

#pragma GCC diagnostic pop

#ifdef __cplusplus
}
#endif
