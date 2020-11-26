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
    int opt =1, optlen=4;

    
    s=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(s==-1){
        perror("socket");
    }
    len =setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (void *)&opt, optlen);
    if(len == -1){
        perror("setsockopt");
        return 0;
    }

    opt=0;
    getsockopt(s, SOL_SOCKET, SO_REUSEADDR, (void *)&opt, &optlen);
    printf("opt : %d\n" , opt);

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

        
    while(1){
        len = read(client_s, buf, 1000);
        if(len ==-1){
            perror("read");
            return 0;
        }
        if(len ==0){
            printf("Disconnected\n");
            break;
        }

        buf[len]='\0';
        printf("%s", buf);
        send(client_s, buf, len, 0);

    }
    write(client_s, "Goodbye", 7);

    close(client_s);
    close(s);

    return 0;
}
