#ifndef _M_XML_H
#define _M_XML_H

#include <mstr/list.h>
#include <mstr/lambda.h>
#include <mstr/string.h>

#ifdef __cplusplus
extern "C" {
#endif

void parse_xml_file(const char* path, lambda_ref* begin, lambda_ref* text, lambda_ref* end);
m_string* m_xml_get_value(m_list* attributes, char* name);
#ifdef __cplusplus
}
#endif

#endif
