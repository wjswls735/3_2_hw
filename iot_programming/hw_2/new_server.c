#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>

typedef struct simple_server {
    
    int s; //server socket
    struct sockaddr_in s_addr;
    socklen_t addr_len;
    int len;
} simple_server;

void zombie_handler(){
    int status;
    pid_t pid;
    pid=wait(&status);
  //  printf("wait : %d\n", pid);
}

int CreateSocket(struct simple_server *s, char *argc){
    
    int opt=1;
    int backlog =5;

    s->s=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    setsockopt(s->s, SOL_SOCKET, SO_REUSEADDR, (void *)&opt, 4);
    if(s->s==-1){
        perror("socket");
    }
    s->s_addr.sin_family=PF_INET;
    s->s_addr.sin_port=htons(atoi(argc));
    s->s_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    memset(&(s->s_addr.sin_zero),0,8);

    if(bind(s->s, (struct sockaddr *)&s->s_addr, sizeof(s->s_addr)) == -1){
        perror("bind");
        return 0;
    }
    if(listen(s->s, backlog)==-1){
        perror("listen");
    }
    return 1;
}
int ConnClient(struct simple_server *s, simple_server *c){
    char *cli_addr;
    c->addr_len=sizeof(struct sockaddr_in);

    c->s=accept(s->s, (struct sockaddr *)&(c->s_addr), &(c->addr_len));
    if(c->s <0){
        switch(errno){
            case EINTR:
                printf("EINTR\n");
            default:
                perror("accpet");
        }
        return 0;
    }
    else{
        printf("Connected (addr : %s , port : %d)\n", inet_ntoa(c->s_addr.sin_addr), ntohs(c->s_addr.sin_port));
        return 1;
    }
}

int readRequest(struct simple_server *s, struct simple_server *c, char *file_name){
    close(s->s);
    int len;
    char buf[1000];
    struct dirent *dir_entry;
    printf("======Request Message======\n");
    len=read(c->s, buf, 1000);
    if(len == -1){
        perror("read");
        return 0;
    }
    else if(len == 0){
        printf("\n");
        return 2;
    }
    buf[len]='\0';

    printf("%s", buf);
    char *p;
    p=strtok(buf, " ");
    p=strtok(NULL, " ");

    char *temp="/";
    if(strcmp(p,temp)==0){
        char *temp="/index.html";
        strcpy(p,temp);
    }
    strcpy(file_name, p);

    char *find_file;
    for(int i=1; i<strlen(p); i++){
        p[i-1]=p[i];
    }
    p[strlen(p)-1]='\0';
    
    
    DIR *dir_info;
    dir_info=opendir(".");
    if(NULL != dir_info){
        while((dir_entry = readdir(dir_info)) != NULL){
            if(strcmp(dir_entry->d_name, p)==0){
                return 1;
            }
        }
    }
    return 2;
    
}
int errorSendPage(struct simple_server *c, char *file_name){
    FILE *fp;
    int file_size;
    char *file_buf;
    char http_msg[100000];
    char *send_data;
    char *file_type;

    fp=fopen("error.html", "r");
    fseek(fp, 0, SEEK_END);
    file_size=ftell(fp);
    fseek(fp, 0, SEEK_SET);
    printf("\n=====Reply Message=====\n");
    sprintf(http_msg, "HTTP/1.1 404 Not Found\r\nContent-Type: %s\r\nContent-Length: %d\r\n\r\n", "text/html", file_size);

    send_data=(char *)malloc(sizeof(char) * file_size);
    fread(send_data, 1, file_size, fp);

    printf("%s", http_msg);
    strcat(http_msg, send_data);
    write(c->s, http_msg, strlen(http_msg));
    
    fclose(fp);
    close(c->s);
    return 0;
}
    
int sendData(struct simple_server *c, char *file_name){
    FILE *fp;
    int file_size;
    char *file_buf;
    char http_msg[100000];
    char *send_data;
    char *file_type;
    char temp_name[20];
    char *check_type;

    fp=fopen(file_name, "rb");
    fseek(fp, 0, SEEK_END);
    file_size=ftell(fp);
    fseek(fp, 0, SEEK_SET);
    //file_name이 조각나지않게 하기위해서 임시 버퍼에 복사

    for(int j=0; j<strlen(file_name); j++){
        temp_name[j]=file_name[j];
    }
    //file_type확인
    check_type=strtok(temp_name, ".");
    check_type=strtok(NULL, ".");  
    char *type1="png";
    char *type2="jpg";

    if(strcmp(check_type, type1)==0){
        file_type="image/png";
    }
    else if(strcmp(check_type,type2)==0){
        file_type="image/jpg";
    }
    else{
        file_type="text/html";
    }

    int packet_idx=1;
    int stat;
    int read_size;
   
    printf("\n=====Reply Message=====\n");
    sprintf(http_msg, "HTTP/1.1 200 OK\r\nContent-Type: %s\r\nContent-Length: %d\r\n\r\n", file_type, file_size);

    send_data=(char *)malloc(sizeof(char) * file_size);

    if(strcmp(file_type, "text/html")==0){
        fread(send_data, 1, file_size, fp);
        printf("%s", http_msg);
        strcat(http_msg, send_data);
        write(c->s, http_msg, strlen(http_msg));
    }
    else{
        printf("%s", http_msg);
        write(c->s, http_msg, strlen(http_msg));
        while(packet_idx == 1){
            read_size=fread(send_data, 1, file_size, fp);
            do{
                stat=write(c->s, send_data, read_size);
            }while(stat<0);
            packet_idx++;
        }
        
    }

    fclose(fp);
    close(c->s);
    return 0;
}

void connHandler(){
    struct sigaction action;
    action.sa_handler =zombie_handler;
    action.sa_flags=0;
    sigemptyset(&action.sa_mask);
    sigaction(SIGCHLD, &action, 0);
}

int main(int argv, char *argc[])
{
    struct simple_server s; //server
    struct simple_server c; //client

    connHandler();
    
    if(CreateSocket(&s, argc[1]) != 1){
       printf("can't make socket\n");
       return 0;
    }

    while(1){
       if(ConnClient(&s, &c)!=1){
           continue;
       }
       if(fork()==0){

           char file_name[100];
           if(readRequest(&s, &c, file_name)==2){
               char p[20]=".";
               strcat(p,file_name);

               int i = 1;
               for(int cnt = 0 ; cnt < strlen(file_name) ; cnt++, i++)
                   p[i] = file_name[cnt];

               errorSendPage(&c, file_name);
               exit(1);
           }
           else{
            
               char p[20]=".";
               strcat(p,file_name);

               int i = 1;
               for(int cnt = 0 ; cnt < strlen(file_name) ; cnt++, i++)
                   p[i] = file_name[cnt];
               sendData(&c, p);
               exit(1);
           }
       }
       else{
           close(c.s);
       }
    }
    close(s.s);
    
    return 0;
}

