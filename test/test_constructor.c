#include <stdio.h>

__attribute__ ((__constructor__))
 void pre_func(void) {
        printf("pre_func\n");
}

int main()
{
  return 0;
}
