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
    struct sockaddr_in addr;
    socklen_t addr_len;
    char msg[1001] = "Hello World" ;
    int backlog=5;
    s=socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(s==-1){
        perror("socket");
    }
    server_addr.sin_family=PF_INET;
    server_addr.sin_port=htons(54321);
    inet_aton("127.0.0.1", &server_addr.sin_addr);
    memset(&(server_addr.sin_zero),0, 8);

    if(connect(s, (struct sockaddr *)&server_addr, sizeof(server_addr))==-1){
        perror("connect");
        return 0;
    }

    addr_len = sizeof(server_addr);
    //wirte(s, msg, strlen(msg));
    while(1){
        printf("Input message: ");
        fgets(msg, 1000, stdin);
        //len = sendto(s, msg, strlen(msg), 0, (struct sockaddr*)&server_addr, addr_len);
        len = send(s, msg, strlen(msg), 0);
        if(len ==-1){
            perror("write");
            close(s);
            return 0;
        }
       // read_len=recvfrom(s,msg,1000,0, (struct sockaddr*)&addr, &addr_len);

        read_len=recv(s,msg,1000,0);
        if(read_len ==-1){
            perror("read");
            return 0;
        }
        
        if(read_len ==0){
            printf("Disconneted");
            break;
        }
        msg[read_len]=0;
        printf("Message from server: %s", msg);
        /*
        msg[len]=0;
        printf("echo : %s\n", msg);
        */
    }

    close(s);
    return 0;
}
