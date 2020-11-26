#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argv, char* argc[]){
    
    int s;
    int len;
    int read_len;
    char msg[1001];

    struct sockaddr_in server_addr;
    socklen_t addr_len;

    /*socket을 생성하는 부분*/
    s=socket(PF_INET, SOCK_STREAM, 0);
    if(s==-1){
        perror("socket");
        return 0;
    }

    server_addr.sin_family=PF_INET;
    /*host의 포트번호*/
    server_addr.sin_port=htons(80);
    inet_aton(argc[1], &server_addr.sin_addr);

    memset(&(server_addr.sin_zero),0,8);

    /*주어진 IP를 통해서 만들어놓은 소켓을 server와 연결*/
    if(connect(s, (struct sockaddr *)&server_addr, sizeof(server_addr)) ==-1){
        perror("connect");
        return 0;
    }
    
    /*socket에 server에게 전하려고했던 명령어 자체를 집어넣음*/
    len=write(s, "GET / HTTP/1.1\r\nHost: 127.0.0.1\r\nConnection: close\r\n\r\n", strlen("GET / HTTP/1.1\r\nHost: 127.0.0.1\r\nConnection: close\r\n\r\n"));
    if(len==-1){
        perror("write");
        close(s);
        return 0;
    }  

    /*server에서 받아오는 값을 화면에 출력*/
    while(1){
        read_len=read(s,msg,1000);
        if(read_len ==-1){
            perror("read");
            return 0;
        }
        if(read_len==0){
            printf("\nEND\n");
            break;
        }
        msg[read_len]=0;
        printf("%s",msg);
    }
    /*close socket*/
    close(s);
    return 0;
}   


