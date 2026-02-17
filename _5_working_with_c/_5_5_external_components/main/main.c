#include <stdio.h>
#include "calc.h"

void app_main(void)
{
    int a=3,b=4;
    printf("(%d,%d):\n", a,b);
    printf("add = %d\n", add(a,b));
    printf("sub = %d\n", sub(a,b));
    printf("mul = %d\n", mul(a,b));
    printf("div = %.2f\n", divm(a,b));
}
