#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/in.h>
#include <stdlib.h>

int main()
{
    int s;
    struct sockaddr_in server_addr;
    socklen_t addr_len;
    char msg[1000] = "Hello World" ;
    int backlog=5;
    s=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(s==-1){
        perror("socket");
    }
    server_addr.sin_family=PF_INET;
    server_addr.sin_port=htons(10000);
    inet_aton("127.0.0.1", &server_addr.sin_addr);
    memset(&(server_addr.sin_zero),0, 8);


    if(connect(s, (struct sockaddr *)&server_addr, sizeof(server_addr)) ==-1){
        perror("connect");
        return 0;
    }

    //wirte(s, msg, strlen(msg));
    send(s, msg, strlen(msg), 0);

    close(s);
    return 0;
}

