#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define BUF_SIZE 100

char escape[]="/q";

pthread_mutex_t mutex;

struct server s;

struct smsg{
    uint16_t Size;
    char Type;
    char data[BUF_SIZE];
};

struct client{
    int fd;
    char name[10];
    struct in_addr cin_addr;
    struct client *next;
    struct client *prev;
};

struct server{
    int server_s, client_s;
    struct sockaddr_in s_addr, c_addr;
    struct smsg msg;
    unsigned int sin_size, len_inet;
    struct client *head;
    struct client *head_pointer;
    int client_number;
    int size;
};



int createSock(char *argv){
    int size;
    int opt=1;
    s.server_s = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(s.server_s, SOL_SOCKET, SO_REUSEADDR, (void *)&opt, 4);
    s.s_addr.sin_family = AF_INET;
    s.s_addr.sin_port = htons(atoi(argv));
    s.s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    memset(&(s.s_addr.sin_zero), 0, 8);
    
    if(bind(s.server_s, (struct sockaddr *)&(s.s_addr), sizeof(struct sockaddr))<0){
        perror("bind");
        return 1;
    }
    
    if(listen(s.server_s, 5) < 0){
        perror("listen");
        return 1;
    }

    s.sin_size = sizeof(struct sockaddr_in);
    return 0;
    
}
void clearData(){
    s.msg.Size=0;
    s.msg.Type='\0';
    for(int i =0; i<99; i++){
        s.msg.data[i]='\0';
    }
}


int recvClientmsg(void *arg){
    int socket=*(int *)arg;
   
    clearData();
    s.size = recv(socket, &(s.msg.Size), 2, 0);
    s.msg.Size = ntohs(s.msg.Size);
    if(s.size<=0){
        return 0;
    }
    s.size = recv(socket, &(s.msg.Type), 1, 0);
    s.size = recv(socket, s.msg.data, s.msg.Size, 0);
  
    for(int i = 0 ; i < strlen(s.msg.data) ; i++){
        printf("%c", s.msg.data[i]);
    }
    printf("\n");
    printf("len : %lu\n", strlen(s.msg.data));
    printf("Type : %c\n", s.msg.Type);
    printf("Recv : %s\n", s.msg.data);
    
    return 1;
}

void sendAllClient(void *arg){
    int socket=*(int *)arg;
    unsigned int len;
    char temp[100];
    
    strncpy(temp, s.head_pointer->name, strlen(s.head_pointer->name));
    temp[strlen(s.head_pointer->name)]=':';
    temp[strlen(s.head_pointer->name)+1]=' ';
    temp[strlen(s.head_pointer->name)+2]='\0';
    strcat(temp, s.msg.data);
    printf("s.head_pointer->name = %s\n",s.head_pointer->name);
    len = strlen(temp);

    for(int i=0; i<s.client_number; i++){ 
        s.size=send(s.head_pointer->fd, &(len), 2, 0);
        s.size=send(s.head_pointer->fd, &(s.msg.Type), 1, 0);
        s.size=send(s.head_pointer->fd, temp, strlen(temp), 0);
        printf("\nTo %s, socket_number = %d, msg = %s \n", s.head_pointer->name, s.head_pointer->fd, temp);
       
        s.head_pointer=s.head_pointer->next;
    }

    for(int i=0; i<99; i++){
        temp[i]='\0';
    }

}

void insertClient(void *arg){

    struct client *cli;
    cli = malloc(sizeof(struct client));
    strncpy(cli->name, s.msg.data, s.msg.Size);
    cli->cin_addr=s.c_addr.sin_addr;
    cli->fd = *(int*)arg;
    if(s.client_number==0){
        s.head = cli;
        s.head_pointer=cli;
        cli->next=cli;
        cli->prev=cli;
    }
    else{
        cli->next=s.head->next;
        s.head->next=cli;
        cli->prev=s.head;
        cli->next->prev = cli;
    }
    s.client_number+=1;
   
}

void deleteClient(int *sock){
    if(s.client_number>1){
        if(s.head_pointer == s.head){
            s.head = s.head->next;
        }
        s.head_pointer->prev->next = s.head_pointer->next;
        s.head_pointer->next->prev = s.head_pointer->prev;
         
        free((s.head_pointer));
        printf("\nfree  s.head_pointer = %#x\n", s.head_pointer);
        s.head_pointer=s.head;
    }
    else{
        if(s.head_pointer == s.head){
            s.head = NULL;
        }
        free(s.head_pointer);
        s.head_pointer=NULL;
    }
    s.client_number-=1;
    close(*sock);
}


void checkHeadPointer(int *socket){
    
    for(int i=0; i<s.client_number; i++){
       if(*socket == s.head_pointer->fd){
           printf("current head_pointer client name = %s\n", s.head_pointer->name);
           break;
       }
       
       s.head_pointer=s.head_pointer->next;
    }
}

void *client_main(void* arg){
    int socket=*(int *)arg;
    free(arg);

    while(1){
        pthread_mutex_lock(&mutex);
        if(recvClientmsg(&socket)){
            checkHeadPointer(&socket); 
            if(s.msg.Type=='m') sendAllClient(&socket);
            else if(s.msg.Type=='c') insertClient(&socket);
            else  {
                deleteClient(&socket);
                pthread_mutex_unlock(&mutex);
                break;
            }
        }
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}


int main(int argc, char *argv[]){
    
    int *arg;
    pthread_t t_id;
    s.client_number=0;

    if(createSock(argv[1]) == 1){
        return 0;
    }

    printf("waiting ... \n");

    while(1){
        s.client_s = accept(s.server_s, (struct sockaddr *)&(s.c_addr), &(s.sin_size));
        if(s.client_s < 0){
            perror("accept");
            return 0;
        }

        arg=malloc(sizeof(int));
        *(int *)arg=s.client_s;

        pthread_create(&t_id, NULL, client_main, arg);
        pthread_detach(t_id);

    }
    close(s.server_s);
    return 0; 
}

