#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
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
    int fd;
    fd=open("test.c", O_WRONLY | O_CREAT, 0644);

    //wirte(s, msg, strlen(msg));
    while(1){
        len=read(s, msg, 1000);
        if(len == -1){
            perror("read");
            close(s);
            return 0;
        }
        if(len == 0){
            printf("Disconnected\n");
            break;
        }
    //    msg[len]=0;
    //    printf("%s", msg);
        write(fd,msg, len);
    }
       
    close(fd);

    close(s);
    return 0;
}
