#ifndef _M_REF_H
#define _M_REF_H

#include <stdatomic.h>
/*

  force disable warning incompatible pointer types
  expansion of BASE_REF_FUNC_INHERIT will assign ref* to void* pointer

*/
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _m_list m_list;
typedef struct _Ref ref;
typedef struct _Weak_Ref weak_ref;

void base_ref_retain(ref*);
void base_ref_release(ref*);
void base_ref_auto_release(ref*);
weak_ref* base_ref_new_weak_ref(ref*);

#define REF_FUNC_MACRO \
  void(*retain)(void*); \
  void(*release)(void*); \
  void(*auto_release)(void*); \
  void(*free)(void*); \
  weak_ref*(*new_weak_ref)(void*);

#define REF_FIELD_MACRO \
  atomic_int ref_count; \
  struct autoreleasenode* pool_ref; \
  m_list* weak_list;

struct _ref_func
{
  REF_FUNC_MACRO
};
typedef struct _ref_func ref_func;

extern ref_func __base_ref_func;

/* base ref functions will be inherited */
#define BASE_REF_FUNC_INHERIT \
  .retain = base_ref_retain, \
  .release = base_ref_release, \
  .auto_release = base_ref_auto_release, \
  .new_weak_ref = base_ref_new_weak_ref

/*
  quick assign ref type to struct
  e.g :
  struct _object_func
  {
    REF_FUNC_MACRO
    void(*next_func_1)(void*);
    void(*next_func_2)(void*);
  };
  typedef struct _object_func object_func;

  struct _object
  {
    CONSTRUCT_REF(object_func)
    int next_field_1;
    long next_field_2;
  };
  typedef struct _object object;
*/
#define CONSTRUCT_REF(__FUNC__) \
  __FUNC__* func; \
  REF_FIELD_MACRO

struct _Ref
{
  CONSTRUCT_REF(ref_func)
};
typedef struct _Ref ref;

struct _Weak_Ref
{
  CONSTRUCT_REF(ref_func)
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
  val->func->auto_release(val);

#ifdef __cplusplus
}
#endif

#endif
