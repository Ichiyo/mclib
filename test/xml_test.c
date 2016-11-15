#include <mstr/xml.h>
#include <utils/file_utils.h>
#include <math/math.h>

#define TEST_MACRO \
  /*123*/ \
  0

int
main (int argc, char *argv[])
{
  const char* flt = "-3.25841e-7 123";
  float f;
  int d;
  sscanf(flt, "%f %d", &f, &d);
  printf("%4.8f %d\n", f, d);

  parse_xml_file("res/cude.dae",

    SAFE_NEW_LAMBDA(void, (int depth, m_string* name, m_list* attributes)
    {
      printf("begin : %s\n",name->content);
      for(int i = 0; i < attributes->size; i += 2)
      {
        m_string* attr_name = (m_string*)attributes->func->get_index(attributes, i);
        m_string* attr_value = (m_string*)attributes->func->get_index(attributes, i + 1);
        printf("\t%s : %s\n",attr_name->content, attr_value->content);
      }
    },0),

    SAFE_NEW_LAMBDA(void, (int depth, m_string* name, m_string* content)
    {

    },0),

    SAFE_NEW_LAMBDA(void, (int depth, m_string* name)
    {
    },0)

  );
	ref_update_auto_release_pool();
	return 0;
}
