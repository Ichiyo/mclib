#ifndef _M_XML_H
#define _M_XML_H

#include <mstr/list.h>
#include <mstr/lambda.h>
#include <mstr/string.h>

#ifdef __cplusplus
extern "C" {
#endif

void parse_xml_file(const char* path, lambda_ref* begin, lambda_ref* text, lambda_ref* end);

#ifdef __cplusplus
}
#endif

#endif
