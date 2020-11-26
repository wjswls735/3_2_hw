#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
    int s;
    int len;
    int read_len;
    struct sockaddr_in server_addr;
    socklen_t addr_len;
    char msg[1001] = "Hello World" ;
    int backlog=5;
    s=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(s==-1){
        perror("socket");
    }
    server_addr.sin_family=PF_INET;
    server_addr.sin_port=htons(54321);
    inet_aton("127.0.0.1", &server_addr.sin_addr);
    memset(&(server_addr.sin_zero),0, 8);


    if(connect(s, (struct sockaddr *)&server_addr, sizeof(server_addr)) ==-1){
        perror("connect");
        return 0;
    }

    //wirte(s, msg, strlen(msg));
    while(1){
        printf("Input your msg[Q to quit] : ");
        fgets(msg, 1000, stdin);
        if(strcmp(msg, "q\n")==0 || strcmp(msg, "Q\n") == 0){
            break;
        }
        len = write(s, msg, strlen(msg));
        if(len==0){
            printf("Send: Disconnected\n");
            break;
        }

        if(len ==-1){
            perror("write");
            close(s);
            return 0;
        }
        printf("len : %d\n", len);
        len=read(s,msg,1000);
        if(len ==-1){
            perror("read");
            return 0;
        }
        
        if(len ==0){
            printf("Disconneted");
            break;
        }
        msg[len]='\0';
        printf("Echo: %s\n", msg);
        
    }
    shutdown(s,SHUT_WR);
    while(1){
        len=recv(s,msg,1000,0);

        if(len == -1){
            perror("read");
            return 0;
        }
        
        else if(len == 0){
            printf("Disconneted\n");
            break;
        }
        msg[len]='\0';
        printf("Echo: %s\n", msg);
    }
    //close(s);
    return 0;
}
