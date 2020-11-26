#include <stdio.h>
int main()
{
    int n;
    scanf("%d", &n);

    for(int i=0; i<n; i++){
        for(int j=0; j<=n; j++){
            if(j==n){
                printf("\n");
                break;
            }
            if(i>=j){
                printf("%d", j+1);
            }
            else
                printf("%c", '*');
        }
    }
    return 0;
}
