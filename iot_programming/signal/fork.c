#include <unistd.h>
#include <stdio.h>

int g= 10;

int main(){
    int l = 25;
    pid_t pid = fork();

    if(pid ==0) {
        g++;
        printf("child  = g : %d , l : %d\n", g, l);
    }
    else{
        l++;
        printf("parent = g : %d , l : %d\n", g, l);
    }
    return 0;
}
