#include <stdio.h>

int iadd(int a, int b){
    int sum=0;
    sum=a+b;
    return sum;
}

int isub(int a, int b){
    int sum=0;
    sum=a-b;
    return sum;
}

int imul(int a, int b) {
    int sum=0;
    sum=a*b;
    return sum;
}

int idiv(int a, int b){
    int sum=0;
    sum=a/b;
    return sum;
}

int main(void)
{
    int a=20, b=10;
    printf("ADD: %d\n", iadd(a, b));    /* a+b */

    printf("SUB: %d\n", isub(a, b));    /* a-b */

    printf("MUL: %d\n", imul(a, b));    /* a*b */

    printf("DIV: %d\n", idiv(a, b));    /* a/b */

    return 0;
}
