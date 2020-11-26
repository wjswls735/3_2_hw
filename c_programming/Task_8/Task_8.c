#include <stdio.h>
#include "calc.h"

int main(){
    int a=2, b=3;
    printf("A+B : %d\n", add(a,b));
    printf("A*B : %d\n", mul(a,b));
    printf("A^2 : %d\n", square(a));
    return 0;
}
