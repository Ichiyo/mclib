#ifndef _M_REF_H
#define _M_REF_H

#include <stdatomic.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _m_list m_list;

#define REF_MACRO \
  void(*retain)(void*); \
  void(*release)(void*); \
  void(*auto_release)(void*); \
  void(*free)(void*); \
  struct _Weak_Ref*(*new_weak_ref)(void*); \
  atomic_int ref_count; \
  struct autoreleasenode* pool_ref; \
  m_list* weak_list;

struct _Ref
{
  REF_MACRO
};
typedef struct _Ref ref;

struct _Weak_Ref
{
  REF_MACRO
  ref* owner;
  int valid;
};
typedef struct _Weak_Ref weak_ref;

struct autoreleasenode
{
  ref* rc;
  struct autoreleasenode* left;
  struct autoreleasenode* right;
};

void ref_init(ref* obj);
void ref_update_auto_release_pool();

#define REF_NEW(__TYPE__, val) \
  __TYPE__* val = calloc(1, sizeof(__TYPE__)); \
  ref_init(val);

#define REF_NEW_AUTO_RELEASE(__TYPE__, val) \
  __TYPE__* val = calloc(1, sizeof(__TYPE__)); \
  ref_init(val); \
  val->auto_release(val);

#ifdef __cplusplus
}
#endif

#endif
