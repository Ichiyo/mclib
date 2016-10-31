#include <stdio.h>
#include <mstr/string.h>
#include <mstr/data.h>
#include <mstr/map.h>
#include <mstr/list.h>
#include <string.h>
#include <stdlib.h>
#include <serialize/serialize.h>
#include <graphic/node.h>
#include <graphic/sprite2d.h>
#include <math/math.h>
#include <utils/file_utils.h>
#include <graphic/image.h>
#include <graphic/texture.h>

static void traverse(unsigned long key, void* data)
{
	printf("key : %ld\n", key);
}

int
main (int argc, char *argv[])
{
	g_image* image = image_new_from_file("wolf.jpg");
	g_texture* tex = texture_new_from_file_char("wolf.jpg");
	g_texture* tex2 = texture_new_from_file_char("wolf.jpg");
	printf("%p | %p\n", tex, tex2);
	m_string* str = new_string();
	m_string* str2 = new_string();
	str->cat_char(str, "Welcome");
	str->cat_char(str, " ");
	str->cat_char(str, "To");
	str->cat_char(str, " Viet Nam");
	str2->cat_str(str2, str);
	str2->cat_char(str2, " :)!");
	m_data* str3 = read_data_from_file("name.txt");
	printf("%s\n", str->content);
	printf("%s\n", str2->content);
	//----
	g_node* node = sprite2d_new();
	node->visit(node);
	//----

	m_map* map = create_map();
	map->insert(map, 0, "Hello !!!", 0);
	map->traverse(map, traverse);

	m_list* list = linked_list_new();
	list->push(list, str, 1);
	list->push(list, str2, 1);
	list->push(list, "texting!!!", 0);
	list->push(list, node, 1);
	m_string* ddd = (m_string*)list->get_index(list, 1);
	printf("%s\n",ddd->content);

	list->remove(list, str2);
	float f = 3.1415926;
	float f2;
	uint32_t fi;

	fi = pack754_32(f);
	f2 = unpack754_32(fi);

	printf("f = %.7f, fi = %lu, f2 = %.7f\n",f, fi, f2);

	weak_ref* weak_image = image->new_weak_ref(image);
	weak_image->retain(weak_image);
	texture_free_cache();
	ref_update_auto_release_pool();
	printf("check image valid : %d\n", weak_image->valid);
	weak_image->release(weak_image);
	return 0;
}
