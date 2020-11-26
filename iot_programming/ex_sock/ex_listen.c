#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/in.h>
#include <stdlib.h>

int main()
{
    int s, client_s;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    socklen_t addr_len;
    char buf[1000];
    int len;
    int backlog=5;
    s=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(s==-1){
        perror("socket");
    }
    server_addr.sin_family=PF_INET;
    server_addr.sin_port=htons(10000);
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

    /*연결요청이 없으면 block됨*/
    client_s=accept(s, (struct sockaddr*)&client_addr, &addr_len);
    if(client_s == -1){
        perror("clients_s");
        return 0;
    }
    
    //len=read(client_s, &buf, 1000);
    len=recv(client_s, &buf, 1000, 0);
    if(len == -1){
        perror("read");
        return 0;
    }
    buf[len]='\0';
    printf("len : %d\n", len);
    printf("%s\n", buf);
   
    close(client_s);
    return 0;
}


