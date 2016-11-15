#ifndef _M_REF_H
#define _M_REF_H

#ifdef linux
#include <stdatomic.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
typedef struct _ref ref;
typedef struct _weak_ref weak_ref;

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

#ifdef linux
#define REF_FIELD_MACRO \
  atomic_int ref_count; \
  struct autoreleasenode* pool_ref; \
  m_list* weak_list;
#else
#define REF_FIELD_MACRO \
  int ref_count; \
  struct autoreleasenode* pool_ref; \
  m_list* weak_list;
#endif

/* base ref functions will be inherited
  e.g :

  // base ref functions
  ref_func __base_ref_func = {
    BASE_REF_FUNC_INHERIT,
    .free = 0
  };
  //-----------------------------------
  //other data function
  EXTEND_REF_FUNC(data_func,
    void(*dosmt)();
  );

  static void free_data(data* d)
  {
    free(d);
  }

  static void data_dosmt()
  {
    // you do what you do !
  }

  static data_func base_data_func =
  {
    BASE_REF_FUNC_INHERIT,
    .free = free_data,
    .dosmt = data_dosmt
  };

*/

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

/*
  quick inherit from ref
  e.g:
  EXTEND_REF_FUNC(object_func,
    void(*next_func_1)(void*);
    void(*next_func_2)(void*);
  );
  EXTEND_REF(object, object_func,
    int next_field_1;
    long next_field_2;
  );
*/
#define EXTEND_REF_FUNC(struct_type, content) \
  struct _##struct_type \
  { \
     REF_FUNC_MACRO \
     content \
  };\
  typedef struct _##struct_type struct_type;

#define EXTEND_REF(struct_type, func, content) \
  struct _##struct_type \
  { \
    CONSTRUCT_REF(func) \
    content \
  }; \
  typedef struct _##struct_type struct_type;

/*
  declare ref and weak_ref use quick declaration type
  ref_func is a ref_func
  ref is a ref
  weak_ref is a ref
  a ha!
*/
EXTEND_REF_FUNC(ref_func,);
extern ref_func __base_ref_func;

EXTEND_REF(ref, ref_func,);
EXTEND_REF(weak_ref,ref_func,
  ref* owner;
  int valid;
);

#define BASE_REF_FUNC_INHERIT \
  .retain = base_ref_retain, \
  .release = base_ref_release, \
  .auto_release = base_ref_auto_release, \
  .new_weak_ref = base_ref_new_weak_ref

#define INHERIT_REF_FUNC BASE_REF_FUNC_INHERIT

/*
  autorelease pool is designed with linked list to remove object quickly
  a ref need to keep track about it in release pool
*/
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

#define QUICK_RETAIN(val) do { if(val) val->func->retain(val); } while(0)
#define QUICK_RELEASE(val) do { if(val) val->func->release(val); } while(0)

#define _0(x,y) x->func->y(x)
#define _1(x,y,a1) x->func->y(x,a1)
#define _2(x,y,a1,a2) x->func->y(x,a1,a2)
#define _3(x,y,a1,a2,a3) x->func->y(x,a1,a2,a3)
#define _4(x,y,a1,a2,a3,a4) x->func->y(x,a1,a2,a3,a4)
#define _5(x,y,a1,a2,a3,a4,a5) x->func->y(x,a1,a2,a3,a4,a5)
#define _6(x,y,a1,a2,a3,a4,a5,a6) x->func->y(x,a1,a2,a3,a4,a5,a6)
#define GET_MACRO(_1,_2,_3,_4,_5,_6,_7,_8,NAME,...) NAME
#define _(...) GET_MACRO(__VA_ARGS__,_6,_5,_4, _3, _2, _1, _0)(__VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif
