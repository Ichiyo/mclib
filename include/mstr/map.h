#ifndef __M_MAP_H
#define __M_MAP_H

#include <base/ref.h>

#ifdef __cplusplus
extern "C" {
#endif

struct m_map_node
{
	void* data;
	unsigned long key;
	struct m_map_node* next;
	int has_ref;
};

struct _m_map
{
	REF_MACRO
	struct m_map_node** table;
	unsigned long size;
};
typedef struct _m_map m_map;

m_map* create_map();
void insert_to_map(m_map* map, unsigned long key, void* data, int is_ref);
void* get_from_map(m_map* map, unsigned long key);
void remove_from_map(m_map* map, unsigned long key);
void traverse_map(m_map* map, void(*)(unsigned long, void*));

#ifdef __cplusplus
}
#endif

#endif
