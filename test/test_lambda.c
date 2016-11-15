#include <stdio.h>
#include <mstr/primitive.h>
#include <mstr/list.h>
#include <stdlib.h>
#include <mstr/lambda.h>

int main(int argc, char const *argv[]) {

  m_int* number = new_int(1234);
  m_int* number_2 = new_int(12345);
  lambda_ref* ret = SAFE_NEW_LAMBDA(void, (double arg1, int arg2){
    printf("hello working here! %d\n", number->ref_count);
    printf("hello working here! %d\n", number_2->ref_count);
    printf("custom data %f | %d\n", arg1, arg2);
  },number, number_2);
  _(ret, retain);

  float t = 99.1;
  ret->callback(t, 88888888888888);
  ref_update_auto_release_pool();
  ret->callback(77.12, 66);
  _(ret, release);
  ref_update_auto_release_pool();
  return 0;
}
