#include <stdio.h>
#include <stdlib.h>
int main(){
    char* num;
    num=malloc(sizeof(char)*5);
    int count=0;
    printf("Enter a number : ");
    scanf("%s", num);
    
    while(num[count]!='\0'){
        count++;
    }
    printf("The number %s has %d digits\n", num, count);
    return 0;
}
