#ifndef _M_LAMBDA_H
#define _M_LAMBDA_H

#include <base/ref.h>
#include <mstr/list.h>

#ifdef __cplusplus
extern "C" {
#endif

EXTEND_REF_FUNC(lambda_func,
  void(*to_guard)(void*, void*);
);

/*
  Clang does not support nested function but has block.
  Block acts "like function" but invoking block as function type
  will generate segment fault !
*/
#if defined(__clang__)
EXTEND_REF(lambda_ref, lambda_func,
  void(^callback)();
  m_list* guards;
);
#else //GNU
EXTEND_REF(lambda_ref, lambda_func,
  void(*callback)();
  m_list* guards;
);
#endif

lambda_ref* new_lambda(void* func, void* guards,...);

#if defined(__clang__)

#define SAFE_NEW_LAMBDA(return_type,body,list...) \
  new_lambda(^body,list,0)

#else //GNU

#define SAFE_NEW_LAMBDA(return_type,body,list...) \
  new_lambda(({return_type __fn__ body __fn__;}),list,0)

#endif

#ifdef __cplusplus
}
#endif

#endif
