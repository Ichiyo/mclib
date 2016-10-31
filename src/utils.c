#include <utils/file_utils.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

m_string* read_string_from_file(const char* path)
{
 FILE* file = fopen(path, "r");
 if(!file) return 0;

 m_string* ret = new_string();
 char buff[1024];
 while(fgets(buff, 1024, file))
 {
   ret->cat_char(ret, buff);
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
    ret->put(ret, buff, count);
  }

  fclose(file);
  return ret;
}

#ifdef __cplusplus
}
#endif
