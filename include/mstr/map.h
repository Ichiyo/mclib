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

EXTEND_REF_FUNC(m_map_func,
	void(*insert)(void*, unsigned long, void*, int);
	void*(*get)(void*, unsigned long);
	void(*remove)(void*, unsigned long);
	void(*traverse)(void*, void(*)(unsigned long, void*));
);

EXTEND_REF(m_map, m_map_func,
	struct m_map_node** table;
	unsigned long size;
);

m_map* create_map();

#ifdef __cplusplus
}
#endif

#endif
