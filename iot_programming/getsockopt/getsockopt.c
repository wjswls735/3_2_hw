#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
int main()
{
    int tcp_sock, udp_sock;
    int opt, oplen = 4;

    tcp_sock= socket(PF_INET, SOCK_STREAM, 0);
    udp_sock= socket(PF_INET, SOCK_DGRAM, 0);

    printf("TCP : %d\n", SOCK_STREAM);
    printf("UDP : %d\n", SOCK_DGRAM);

    getsockopt(tcp_sock, SOL_SOCKET, SO_TYPE, (void *)&opt, &oplen);
    printf("Sockopt : %d\n", opt);
    getsockopt(udp_sock, SOL_SOCKET, SO_TYPE, (void *)&opt, &oplen);
    printf("Sockopt : %d\n", opt);

    return 0;
}
