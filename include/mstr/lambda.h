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

EXTEND_REF(lambda_ref, lambda_func,
  void(*callback)();
  m_list* guards;
);

lambda_ref* new_lambda(void* func, void* guards,...);

#define SAFE_NEW_LAMBDA(return_type,body,list...) \
  new_lambda(({return_type __fn__ body __fn__;}),list,0);

#ifdef __cplusplus
}
#endif

#endif
