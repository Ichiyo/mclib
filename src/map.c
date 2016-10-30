#include "mstr/map.h"
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

static void free_map(struct m_map* map)
{
	for(unsigned long i = 0; i < map->size; ++i)
	{
		struct m_map_node* node = map->table[i];
		while(node)
		{
			struct m_map_node* next = node->next;
			if(node->has_ref)
			{
				((ref*)node->data)->release(node->data);
			}
			free(node);
			node = next;
		}
	}
	free(map->table);
	free(map);
}

static void resize(struct m_map* map, unsigned long new_size)
{
	map->table = realloc(map->table, new_size * sizeof(struct m_map_node*));
	map->size = new_size;
}

static unsigned long hash(unsigned long key)
{
	return key % 10;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
struct m_map* create_map()
{
	struct m_map* m = malloc(sizeof(struct m_map));
	m->table = calloc(10 ,sizeof(struct m_map_node*));
	m->size = 10;
	ref_init(m);
	m->auto_release(m);
	m->free = free_map;
	return m;
}
#pragma GCC diagnostic pop

void insert_to_map(struct m_map* map, unsigned long key, void* data, int is_ref)
{
	if(is_ref)
	{
		((ref*)data)->retain(data);
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
					((ref*)node->data)->release(node->data);
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

void* get_from_map(struct m_map* map, unsigned long key)
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

void remove_from_map(struct m_map* map, unsigned long key)
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
					((ref*)node->data)->release(node->data);
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

void traverse_map(struct m_map* map, void(*callback)(unsigned long, void*))
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

#ifdef __cplusplus
}
#endif
