#include <stdio.h>
#define N 10

int main()
{
    int a[N];
    printf("Enter  %d numbers: ", N);
    float sum=0;
    int max=0;
    for (int i=0; i<N; i++){
        scanf("%d", &a[i]);
        sum+=(float)a[i];
        if(max<a[i]){
            max=a[i];
        }
    }
    printf("Average is %.3f\n" , sum/10);
    printf("Max value is %d\n" , max);
    return 0;
}
