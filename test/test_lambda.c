#include <stdio.h>
#include <mstr/primitive.h>
#include <mstr/list.h>
#include <stdlib.h>
#include <mstr/lambda.h>

int main(int argc, char const *argv[]) {

  m_int* number = new_int(1234);
  m_int* number_2 = new_int(12345);
  lambda_ref* ret = SAFE_NEW_LAMBDA(void, (int arg1, int arg2){
    printf("hello working here! %d\n", number->ref_count);
    printf("hello working here! %d\n", number_2->ref_count);
    printf("custom data %d | %d\n", arg1, arg2);
  },number, number_2);

  ret->func->retain(ret);
  ret->callback(99, 88);
  ref_update_auto_release_pool();
  ret->callback(77, 66);
  ret->func->release(ret);
  ref_update_auto_release_pool();
  return 0;
}
