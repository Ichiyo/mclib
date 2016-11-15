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

  IMPORTAINT:
  function in GNU or block in CLANG needs declare arguments of these types :
    - pointer : void*, name*...
    - double : can not use float because of implicit conversion from float to double when pushing float to call stack
               results 8 bytes in stack for argument,
               if argument declared as float then function will receive only 4 bytes from stack --> wrong bi
    - int/long/char...
*/
#if defined(__clang__)

EXTEND_REF(lambda_ref, lambda_func,
  void*(^callback)();
  m_list* guards;
);

#define __assignable __block

#else //GNU

EXTEND_REF(lambda_ref, lambda_func,
  void*(*callback)();
  m_list* guards;
);

#define __assignable 

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
