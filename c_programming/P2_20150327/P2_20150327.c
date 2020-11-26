#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    srand((unsigned)time(0));
    unsigned int r_int=rand()*rand();

    unsigned int key=r_int % 1001;
   // key=0;
    int n;
    int count =0;
    while(1){
        printf("Put your guess: ");
        scanf("%d", &n);
        if( key > n){
            printf("The key is higher than %d\n", n);
            if(key%n==0){
                printf("The key is a multiple of %d\n", n);
            }
        }
        else if(key<n){
            printf("The key is lower than %d\n", n);
            if(key!=0){
                if(n%key==0){
                    printf("The key is a multiple of %d\n", n);
                }
            }
        }
        else{
            if(count ==0){
                printf("Feeling lucky! the number was %d\n", n);
            }
            else{
                if(key ==0 || key ==1000){
                    printf("You got the extreme number! the number was %d\n", n);
                }
                else{
                    printf("Player won! the number was %d\n", n);
                }

            }
            return 0;
        }
        count++;
        if(count >9){
            printf("Computer won! the number was %d\n", key);
            return 0;
        }
    }

    return 0;
}

