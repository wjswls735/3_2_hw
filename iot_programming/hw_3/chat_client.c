#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>

#define BUF_SIZE 100

struct smsg{
    uint16_t Size;
    char Type;
};

char escape[] = "/q\n";

void *Thread_main(void *arg)
{
    int size;
    char buf[BUF_SIZE];
    int server_s = *(int *)arg;
    struct smsg msg;

    while((size = read(0, buf, BUF_SIZE)) > 0){
        buf[size - 1] = '\0';
        if(strcmp(buf, "/q") == 0){
            printf("exit\n");
            msg.Size = htons(0);
            msg.Type = 'q';
            send(server_s, (char*)&msg.Size, 2, 0);
            send(server_s, (char*)&msg.Type, 1, 0);
            shutdown(server_s, SHUT_WR);
            break;
        }
        else{
            msg.Size = htons(strlen(buf));
            msg.Type = 'm';
            char *send_msg = (char*)malloc(sizeof(char) * msg.Size);
            strcpy(send_msg, buf);

            send(server_s, (char*)&msg.Size, 2, 0);
            send(server_s, (char*)&msg.Type, 1, 0);
            send(server_s, send_msg, strlen(send_msg), 0);

            free(send_msg);
        }
    }

    return NULL;
}

void insertClient(int *sockfd, struct smsg* msg, char *name){
    msg->Size = htons(strlen(name));
    msg->Type = 'c';
    char *send_msg = (char *)malloc(sizeof(char) * msg->Size);
    strcpy(send_msg, name);

    send(*sockfd, (char*)&(msg->Size), 2, 0);
    send(*sockfd, (char*)&(msg->Type), 1, 0);
    send(*sockfd, send_msg, strlen(send_msg), 0);
    free(send_msg);
}


int main(int argc, char* argv[]){

    int sockfd;
    struct sockaddr_in my_addr;
    unsigned int sin_size;
    char *buf;

    if(argc < 3){
        fprintf(stderr, "Usage : %s <IP> <PORT> <NAME>\n", argv[0]);
        return 0;
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(atoi(argv[2]));
    my_addr.sin_addr.s_addr = inet_addr(argv[1]);
    memset(&(my_addr.sin_zero), 0, 8);

    sin_size = sizeof(struct sockaddr_in);

    if(connect(sockfd, (struct sockaddr *)&my_addr, sin_size) < 0){
        perror("connect");
        return 0;
    }

    printf("Connected. (/q)\n");
    
    struct smsg msg;
    insertClient(&sockfd, &msg, argv[3]);
   
    pthread_t t_id;
    pthread_create(&t_id, NULL, Thread_main, (void*)&sockfd);
    pthread_detach(t_id);

    while(1){
        int size = recv(sockfd, &msg.Size, 2, 0);
        
        if(size ==0){
            printf("Disconnected\n");
            break;
        }
        if(size == -1){
            perror("Error\n");
            return 0;
        }

        size = recv(sockfd, &msg.Type, 1, 0);
        msg.Size = ntohs(msg.Size);

        buf = (char*)malloc(sizeof(char) * msg.Size);
        size = recv(sockfd, buf, msg.Size, 0);
        buf[size] = '\0';
        printf("%s\n", buf);
        free(buf);
    }

    close(sockfd);
    return 0;
}

