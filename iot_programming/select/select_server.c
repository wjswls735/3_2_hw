#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>

void zombie_handler(){
    int status;
    pid_t pid;
    
    pid=wait(&status);
    printf("wait : %d\n", pid);
}

int main()
{
    int s, client_s;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    socklen_t addr_len;
    char buf[11];
    int len;
    int backlog=5;
    fd_set readfds, readtemp;
    int max_fd=0;
    int result;

    struct sigaction action;
    action.sa_handler = zombie_handler;
    action.sa_flags=0;
    sigemptyset(&action.sa_mask);

    sigaction(SIGCHLD, &action, 0);

    s=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(s==-1){
        perror("socket");
    }
    server_addr.sin_family=PF_INET;
    server_addr.sin_port=htons(54321);
    server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    memset(&(server_addr.sin_zero),0, 8);
 
    if((bind(s,(struct sockaddr*)&server_addr, sizeof(server_addr)))==-1){
        perror("bind");
        return 0;
    }
    if(listen(s, backlog)==-1){
        perror("listen");
    }

    addr_len=sizeof(struct sockaddr_in);
    FD_ZERO(&readfds);
    FD_SET(s, &readfds);
    max_fd = s;

    while(1){
        readtemp=readfds;
        result=select(max_fd+1, &readtemp, NULL, NULL, NULL);
        if(result ==-1){
            perror("select");
            return 0;
        }
        
        for(int i=0; i<max_fd+1; i++){
            if(FD_ISSET(i, &readtemp)){
                if(i == s){
                    client_s=accept(s, (struct sockaddr *)&client_addr, &addr_len);
                    if(client_s < 0){
                        switch(errno){
                            case EINTR:
                                continue;
                            default:
                                perror("accept");
                        }
                        return 0;
                    } 
                    printf("connnected\n"); 
                    FD_SET(client_s, &readfds);
                    if(max_fd < client_s){
                        max_fd = client_s;
                    }
                }
                else{
                    //DATA
                    len = read(i, buf, 1000);
                    if(len ==-1){
                        perror("read");
                        return 0;
                    }
                    else if(len ==0){
                        FD_CLR(i, &readfds);
                        close(i);
                        printf("Disconnected\n");
                    }

                    buf[len]='\0';
                   // buf[len]=0;
                    send(i, buf, len, 0);
                }
            }
        }
    }
    close(s);

    return 0;
}
