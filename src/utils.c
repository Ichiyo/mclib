#include <utils/file_utils.h>
#include <stdio.h>
#include <base/platform.h>

#ifdef __cplusplus
extern "C" {
#endif

#if TARGET_PLATFORM != PLATFORM_IOS

FILE* open_file(const char* path)
{
  return fopen(path, "r");
}

m_string* read_string_from_file(const char* path)
{
 FILE* file = fopen(path, "r");
 if(!file) return 0;

 m_string* ret = new_string();
 char buff[1024];
 while(fgets(buff, 1024, file))
 {
   ret->func->cat_char(ret, buff);
 }
 fclose(file);
 return ret;
}

m_data* read_data_from_file(const char* path)
{
  FILE* file = fopen(path, "r");
  if(!file) return 0;

  m_data* ret = data_new();
  char buff[1024];
  unsigned int count = 0;
  while(count = fread(buff, 1, 1024, file))
  {
    ret->func->put(ret, buff, count);
  }

  fclose(file);
  return ret;
}

#endif

#ifdef __cplusplus
}
#endif
