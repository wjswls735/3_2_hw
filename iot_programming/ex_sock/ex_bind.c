#include <stdio.h>
#include <sys/socket.h> /*socket 만들 경우 필요한 헤더*/
#include <sys/types.h> /*socket 만들 경우 필요한 헤더*/
#include <fcntl.h>
#include <arpa/inet.h>  /*struct sockaddr_in, inet_aton이 구성되있는 헤더*/
#include <netinet/in.h> /*IPPROTO_TCP/UDP가 있는 헤더*/
#include <string.h>     /*memset*/
int main()
{
    int sd;                             //socket descriptor
    char addr_str[]="127.0.0.1";     //ip address ->str
    unsigned int addr;
    unsigned int* len_inet;
    struct sockaddr_in my_addr, get_addr;  //had sin_family & sin_port & (struct in_addr)sin_addr & sin_zero

    //socket 생성
    //sd = socket(PF_INET, SOCK_STREAM, 0); 
    /* 끝에 0을 넣으면 자동으로 TCP인지 UDP인지 맞춰줌*/
    //sd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if((sd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP))==-1){
        perror("socket");
    }

    /*addr 초기화시켜줘야함 -> 초기화를 안했서 비었을경우 에러가 발생할 수 있음*/
    memset(&(my_addr), 0, sizeof(my_addr));
    memset(&(get_addr), 0, sizeof(get_addr));

    /*address를 binary로 바꿔서 sin_addr에 넣음 "Big Endian" 형식임*/
    /*inet_aton의 경우는 return값이 1 || 0  임 -> 1111.1111.1111.1111을 못쓰는 경우를 막기위해서*/
    /*inet_ntoa의 경우는 return값이 1 || -1 임*/
    if((addr=inet_aton(addr_str, &(my_addr.sin_addr))) == 0)
    {
        printf("Network ordered addr : %#x\n", my_addr.sin_addr.s_addr);
        /* INADDR_ANY == 0 && 어느 주소로 요청이 와도 받아드림 -> server의 경우에만 가능함*/
        /* s_addr이 32bit이기 때문에 htonl을 사용 */
        my_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    }
   // printf("my_addr.sin_addr.s_addr : %#x\n", my_addr.sin_addr.s_addr);
    my_addr.sin_family=PF_INET;         //socket type
    my_addr.sin_port=htons(6379);       //socket의 port를 입력
    *len_inet=sizeof(my_addr);          

//    printf("Socket IP : %s, PORT : %u\n", inet_ntoa(my_addr.sin_addr), (unsigned)ntohs(my_addr.sin_port));

    /*socketaddr의 경우 sin_family와 sa_data만 들고있는 구조체*/
    if((bind(sd, (struct sockaddr *)&my_addr, sizeof(my_addr)) == -1)){
        /* perror의 경우 error가 났을 경우 error의 내용을 문자로 알려줌*/
        /* errno의 경우는 error가 났을 경우 숫자를 알려줌 */
        perror("bind");
        return 0;
    }

    int getsock;
    int getpeer;
    /*자신의 주소를 얻음*/
    if((getsock=getsockname(sd, (struct sockaddr *)&get_addr, (socklen_t *)len_inet)) == -1){
        perror("getsockname");
        return 0;
    }
    printf("Socket IP : %s, PORT : %u\n", inet_ntoa(get_addr.sin_addr), (unsigned)ntohs(get_addr.sin_port));
    printf("getsockname = %d \n", getsock);

    /*전송해준 client의 주소를 얻음*/
    if((getpeer=getpeername(sd, (struct sockaddr *)&get_addr, (socklen_t *)len_inet)) == -1){
        perror("getpeername");
        return 0;
    }
    printf("getpeername = %d\n", getpeer);

    return 0;
}
