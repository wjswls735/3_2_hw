#include <stdio.h>

int main()
{
    int answer=1;
    while(1){
        int n;
        printf("Put the value of n: ");
        scanf("%d", &n);
        if (n==0){
            return 0;
        }
        for(int i=0; i<n; i++){
            answer*=3;
        }
        printf("3^%d is %d\n", n, answer);
        answer=1;

    }
    return 0;
}
        

