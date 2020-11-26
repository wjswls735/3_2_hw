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
    int s, client_s;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    socklen_t addr_len;
    char buf[1001];
    int len;
    int backlog=5;
    int ops, op, o[100];
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

    client_s=accept(s, (struct sockaddr *)&client_addr, &addr_len);
    if(client_s==-1){
        perror("accept");
        return 0;
    }
    len=read(client_s, &ops, 1);

    for(int i=0; i<ops; i++){
        /*꼭 4바이트가 전달되는것은 아니니 4바이트씩 받고싶다면 검사를 계속해줘야함*/
        read(client_s,&o[i], 4);
        o[i]=ntohl(o[i]);
    }
    
    read(client_s, &op, 1);

    int result =0;
    switch(op){
        case '+': 
            for(int i=0; i<ops; i++){
                result+=o[i];
            }
            break;
        case '-': 
            for(int i=0; i<ops; i++){
                result-=o[i];
            }
            break;
    }
    result=htonl(result);
    write(client_s, &result, 4);
    close(s);

    return 0;
}
