#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int s;
    int len;
    int read_len;
    struct sockaddr_in server_addr;
    socklen_t addr_len;
    char msg[1001] = "Hello World" ;
    int backlog=5;
    int ops;
    int o[100];
    char op;

    if(argc !=3){
        printf("needs 3 args\n");
        return 0;
    }
    
    printf("ops : ");
    scanf("%d", &ops);

    for(int i=0; i<ops; i++){
        printf("operand%d: ", i);
        scanf("%d", &o[i]);
    }
    printf("op : ");
    scanf(" %c", &op);

    s=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(s==-1){
        perror("socket");
    }
    server_addr.sin_family=PF_INET;
    server_addr.sin_port=htons(atoi(argv[2]));
    inet_aton(argv[1], &server_addr.sin_addr);
    memset(&(server_addr.sin_zero),0, 8);


    if(connect(s, (struct sockaddr *)&server_addr, sizeof(server_addr)) ==-1){
        perror("connect");
        return 0;
    }

    int fd;
    fd = open("output.txt", O_WRONLY | O_CREAT, 0644);

    write(s, &ops, 1);
    write(fd, &ops, 1);
    for(int i=0; i<ops; i++){
        o[i]=htonl(o[i]);
        write(s, &o[i], 4);
        write(fd, &o[i], 4);
    }
    write(s, &op, 1);
    write(fd, &op, 1);

    read(s, &ops, 4);
    ops=ntohl(ops);
    printf("result = %d\n", ops); 

//    write(s, &d, sizeof(struct data));
//    write(fd, &d, sizeof(struct data));
    close(fd);

    close(s);
    return 0;
}
