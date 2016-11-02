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

struct _m_map_func
{
	REF_FUNC_MACRO
	void(*insert)(void*, unsigned long, void*, int);
	void*(*get)(void*, unsigned long);
	void(*remove)(void*, unsigned long);
	void(*traverse)(void*, void(*)(unsigned long, void*));
};
typedef struct _m_map_func m_map_func;

struct _m_map
{
	CONSTRUCT_REF(m_map_func)
	struct m_map_node** table;
	unsigned long size;
};
typedef struct _m_map m_map;

m_map* create_map();

#ifdef __cplusplus
}
#endif

#endif
