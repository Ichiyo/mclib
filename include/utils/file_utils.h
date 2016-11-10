#ifndef _M_FILE_UTILS_H
#define _M_FILE_UTILS_H

#include <mstr/string.h>
#include <mstr/data.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif
FILE* open_file(const char* file);
m_string* read_string_from_file(const char* file);
m_data* read_data_from_file(const char* file);

#ifdef __cplusplus
}
#endif

#endif
