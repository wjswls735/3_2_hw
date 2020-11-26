#include<stdio.h>
#define MAX 3
int main(){
    short num[MAX];
    short sum=0;
    printf("Put three integer :");
    scanf("%hd,%hd,%hd", &num[0], &num[1], &num[2]);
    for(int i=0; i<MAX; i++){
        sum+=num[i];
    }
    printf("The result is %hd\n", sum);
    return 0;
}
