#include "mstr/map.h"
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

static void free_map(m_map* map)
{
	for(unsigned long i = 0; i < map->size; ++i)
	{
		struct m_map_node* node = map->table[i];
		while(node)
		{
			struct m_map_node* next = node->next;
			if(node->has_ref)
			{
				((ref*)node->data)->func->release(node->data);
			}
			free(node);
			node = next;
		}
	}
	free(map->table);
	free(map);
}

static void resize(m_map* map, unsigned long new_size)
{
	map->table = realloc(map->table, new_size * sizeof(struct m_map_node*));
	map->size = new_size;
}

static unsigned long hash(unsigned long key)
{
	return key % 10;
}

static void insert_to_map(m_map* map, unsigned long key, void* data, int is_ref)
{
	if(is_ref)
	{
		((ref*)data)->func->retain(data);
	}
	unsigned long h = hash(key);
	if(h >= map->size)
	{
		resize(map, h + 1);
	}

	if(map->table[h] == 0)
	{
		map->table[h] = calloc(1, sizeof(struct m_map_node));
		map->table[h]->data = data;
		map->table[h]->key = key;
		map->table[h]->has_ref = is_ref;
	}
	else
	{
		struct m_map_node* node = map->table[h];
		while(1)
		{
			if(node->key == key)
			{
				if(node->has_ref)
				{
					((ref*)node->data)->func->release(node->data);
				}
				node->data = data;
				node->has_ref = is_ref;
				goto exit;
			}
			if(node->next) node = node->next;
			else break;
		}
		node->next = calloc(1, sizeof(struct m_map_node));
		node->next->data = data;
		node->next->key = key;
		node->next->has_ref = is_ref;
		goto exit;
	}
	exit:;
}

static void* get_from_map(m_map* map, unsigned long key)
{
	unsigned long h = hash(key);
	if(h < map->size)
	{
		struct m_map_node* node = map->table[h];
		if(!node) return 0;
		while(node)
		{
			if(node->key == key) return node->data;
			node = node->next;
		}
	}
	return 0;
}

static void remove_from_map(m_map* map, unsigned long key)
{
	unsigned long h = hash(key);
	if(h < map->size)
	{
		struct m_map_node* node = map->table[h];
		if(!node) return;
		struct m_map_node* prev = 0;
		while(node)
		{
			if(node->key == key)
			{
				if(prev)
				{
					prev->next = node->next;
				}
				else
				{
					map->table[h] = node->next;
				}
				if(node->has_ref)
				{
					((ref*)node->data)->func->release(node->data);
				}
				free(node);
				goto exit;
			}
			prev = node;
			node = node->next;
		}
	}
	exit:;
}

static void traverse_map(m_map* map, void(*callback)(unsigned long, void*))
{
	for(unsigned long i = 0; i < map->size; ++i)
	{
		struct m_map_node* node = map->table[i];
		while(node)
		{
			callback(node->key, node->data);
			node = node->next;
		}
	}
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"

static m_map_func base_m_map_func =
{
	BASE_REF_FUNC_INHERIT,
	.free = free_map,
	.insert = insert_to_map,
	.get = get_from_map,
	.remove = remove_from_map,
	.traverse = traverse_map
};

m_map* create_map()
{
	REF_NEW_AUTO_RELEASE(m_map, m)
	m->table = calloc(10 ,sizeof(struct m_map_node*));
	m->size = 10;
	m->func = &base_m_map_func;
	return m;
}
#pragma GCC diagnostic pop

#ifdef __cplusplus
}
#endif
