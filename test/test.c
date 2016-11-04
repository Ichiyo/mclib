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
	g_image* image = image_new_from_file("res/wolf.jpg");
	g_texture* tex = texture_new_from_file_char("res/wolf.jpg");
	g_texture* tex2 = texture_new_from_file_char("res/wolf.jpg");
	printf("%p | %p\n", tex, tex2);
	m_string* str = new_string();
	m_string* str2 = new_string();
	str->func->cat_char(str, "Welcome");
	str->func->cat_char(str, " ");
	str->func->cat_char(str, "To");
	str->func->cat_char(str, " Viet Nam");
	str2->func->cat_str(str2, str);
	str2->func->cat_char(str2, " :)!");
	m_data* str3 = read_data_from_file("res/name.txt");
	printf("%s\n", str->content);
	printf("%s\n", str2->content);
	//----
	g_node* node = sprite2d_new();
	g_node* node2 = sprite2d_new();
	node->func->add_child(node, node2);
	node->func->visit(node, matrix4_identity, 0);
	//----

	m_map* map = create_map();
	map->func->insert(map, 0, "Hello !!!", 0);
	map->func->traverse(map, traverse);
	m_list* list = linked_list_new();
	list->func->push(list, str, 1);
	list->func->push(list, str2, 1);
	list->func->push(list, "texting!!!", 0);
	list->func->push(list, node, 1);
	m_string* ddd = (m_string*)list->func->get_index(list, 1);
	printf("%s\n",ddd->content);

	list->func->remove(list, str2);
	float f = 3.1415926;
	float f2;
	uint32_t fi;

	fi = pack754_32(f);
	f2 = unpack754_32(fi);

	printf("f = %.7f, fi = %lu, f2 = %.7f\n",f, fi, f2);

	weak_ref* weak_image = tex->func->new_weak_ref(tex);
	weak_image->func->retain(weak_image);
	texture_free_cache();
	ref_update_auto_release_pool();
	printf("check image valid : %d\n", weak_image->valid);
	weak_image->func->release(weak_image);
	return 0;
}
