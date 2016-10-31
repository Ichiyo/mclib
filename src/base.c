#include <base/ref.h>
#include <stddef.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

static struct autoreleasenode* begin = 0;
static struct autoreleasenode* end = 0;
static pthread_mutex_t autorelease_lock;

static __inline__ void try_release_ref(ref* obj)
{
  pthread_mutex_lock(&autorelease_lock);
  if(obj->pool_ref)
  {
    struct autoreleasenode* right = obj->pool_ref->right;
    struct autoreleasenode* left = obj->pool_ref->left;
    if(obj->pool_ref == begin)
    {
      if(right)
      {
        right->left = NULL;
      }
      begin = right;
      if(begin == end) end = NULL;
    }
    else if(obj->pool_ref == end)
    {
      if(left)
      {
        left->right = NULL;
      }
      end = left;
      if(end == begin) end = NULL;
    }
    else
    {
      left->right = right;
      right->left = left;
    }
    free(obj->pool_ref);
    obj->pool_ref = NULL;
  }
  pthread_mutex_unlock(&autorelease_lock);
}

static void ref_retain(ref* obj)
{
  obj->ref_count++;
}

static void ref_release(ref* obj)
{
  obj->ref_count--;
  if(obj->ref_count == 0)
  {
    try_release_ref(obj);
    if(obj->free)
    {
      obj->free(obj);
    }
    #ifdef APP_DEBUG
    else
    {      
        printf("not set free funciton - please fix!!!\n");
    }
    #endif
    #ifdef APP_DEBUG
      printf("ref freed!\n");
    #endif
  }
}

static void ref_auto_release(ref* obj)
{
  pthread_mutex_lock(&autorelease_lock);
  if(!obj->pool_ref)
  {
    obj->pool_ref = calloc(1, sizeof(struct autoreleasenode));
    obj->pool_ref->rc = obj;
    if(!begin)
    {
      begin = obj->pool_ref;
    }
    else
    {
      if(!end)
      {
        begin->right = obj->pool_ref;
        obj->pool_ref->left = begin;
        end = obj->pool_ref;
      }
      else
      {
        end->right = obj->pool_ref;
        obj->pool_ref->left = end;
        end = obj->pool_ref;
      }
    }
  }
  pthread_mutex_unlock(&autorelease_lock);
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
void ref_init(ref* obj)
{
  obj->retain = ref_retain;
  obj->release = ref_release;
  obj->auto_release = ref_auto_release;
  obj->ref_count = 1;
  obj->pool_ref = NULL;
}
#pragma GCC diagnostic pop

void ref_update_auto_release_pool()
{
  while(begin)
  {
    ref* obj = begin->rc;
    try_release_ref(obj);
    obj->release(obj);
  }
}

#ifdef __cplusplus
}
#endif
