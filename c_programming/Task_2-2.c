#include<stdio.h>
#define MAX 3
int main(){
    short num[MAX]; //short는 -32,768 to 32,767 까지 정수를 허용함  
    short sum=0; //-32,768 to 32,767 이 두수를 넘어가는 범위는 허용하지않음
    printf("Put three integer :");
    scanf("%hd,%hd,%hd", &num[0], &num[1], &num[2]);
    for(int i=0; i<MAX; i++){
        sum+=num[i];
    }
    printf("The result is %hd\n", sum); 
    /*%hd이기 때문에 20000+30000+40000의 결과는 32,767을 초과하기 때문에 제대로 된 결과값이 나오지 않음*/
    return 0;
}
