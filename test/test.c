#include <stdio.h>
#include <mstr/string.h>
#include <mstr/map.h>
#include <mstr/list.h>
#include <string.h>
#include <stdlib.h>
#include <serialize/serialize.h>
#include <graphic/node.h>
#include <graphic/sprite2d.h>
#include <math/math.h>

static void traverse(unsigned long key, void* data)
{
	printf("key : %ld\n", key);
}

int
main (int argc, char *argv[])
{
	struct m_string* str = new_string();
	struct m_string* str2 = new_string();
	mstr_char(str, "Welcome");
	mstr_char(str, " ");
	mstr_char(str, "To");
	mstr_char(str, " Viet Nam");
	mstr_mstr(str2, str);
	mstr_char(str2, " :)!");
	printf("%s\n", str->content);
	printf("%s\n", str2->content);
	//----
	struct g_node* node = sprite2d_new();
	node->visit(node);
	//----

	struct m_map* map = create_map();
	insert_to_map(map, 0, "Hello !!!", 0);
	traverse_map(map, traverse);

	m_list* list = linked_list_new();
	list->push(list, str, 1);
	list->push(list, str2, 1);
	list->push(list, "texting!!!", 0);
	float f = 3.1415926;
	float f2;
	uint32_t fi;

	fi = pack754_32(f);
	f2 = unpack754_32(fi);

	printf("f = %.7f, fi = %lu, f2 = %.7f\n",f, fi, f2);

	ref_update_auto_release_pool();
	return 0;
}
