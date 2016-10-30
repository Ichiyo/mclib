#ifndef _M_REF_H
#define _M_REF_H

#include <stdatomic.h>

#ifdef __cplusplus
extern "C" {
#endif

#define REF_MACRO \
  void(*retain)(void*); \
  void(*release)(void*); \
  void(*auto_release)(void*); \
  void(*free)(void*); \
  atomic_int ref_count; \
  struct autoreleasenode* pool_ref;

struct _Ref
{
  REF_MACRO
};
typedef struct _Ref ref;

struct autoreleasenode
{
  ref* rc;
  struct autoreleasenode* left;
  struct autoreleasenode* right;
};

void ref_init(ref* obj);
void ref_update_auto_release_pool();

#ifdef __cplusplus
}
#endif

#endif