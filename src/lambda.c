#include <mstr/lambda.h>
#include <stdarg.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

static void lambda_free(lambda_ref* arg)
{
  if(arg->guards)
  {
    arg->guards->func->release(arg->guards);
  }
  free(arg);
}

static void lambda_to_guard(lambda_ref* self, void* arg)
{
  if(!self->guards)
  {
    self->guards = linked_list_new();
    self->guards->func->retain(self->guards);
  }
  self->guards->func->push(self->guards, arg, 1);
}

static lambda_func base_lambda_func =
{
  BASE_REF_FUNC_INHERIT,
  .free = lambda_free,
  .to_guard = lambda_to_guard
};

lambda_ref* new_lambda(void* func, void* guards, ...)
{
  REF_NEW_AUTO_RELEASE(lambda_ref, ret);
  ret->func = &base_lambda_func;
  ret->callback = func;

  /* initialize valist for num number of arguments */
  va_list valist;
  va_start(valist, guards);
  void* p = guards;
  while(p)
  {
      ret->func->to_guard(ret, p);
      p = va_arg(valist, void*);
  }
  /* clean memory reserved for valist */
  va_end(valist);

  return ret;
}

#ifdef __cplusplus
}
#endif
