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
	void(*insert)(struct _m_map*, unsigned long, void*, int);
	void*(*get)(struct _m_map*, unsigned long);
	void(*remove)(struct _m_map*, unsigned long);
	void(*traverse)(struct _m_map*, void(*)(unsigned long, void*));
};
typedef struct _m_map m_map;

m_map* create_map();

#ifdef __cplusplus
}
#endif

#endif
