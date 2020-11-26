#include <unistd.h>
#include <stdio.h>
#include <signal.h>
int g= 10;

void zombie(){
    int status;
    wait(&status);

    printf("%08x\n", status);
}

int main(){
    int l = 25;
    pid_t pid = fork();
    
    struct sigaction act;

    act.sa_handler = zombie;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);

    sigaction(SIGCHLD, &act, 0);

    if(pid ==0) {
        sleep(1);
        g++;
        printf("child  = g : %d , l : %d\n", g, l);

    }
    else{
        sleep(100);
        l++;
        printf("parent = g : %d , l : %d\n", g, l);
    }
    return 0;
}
