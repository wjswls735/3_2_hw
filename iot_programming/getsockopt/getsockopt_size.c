#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
int main()
{
    int tcp_sock, udp_sock;
    int opt, oplen = 4;

    tcp_sock= socket(PF_INET, SOCK_STREAM, 0);
    udp_sock= socket(PF_INET, SOCK_DGRAM, 0);

    opt = 10000000;
    setsockopt(tcp_sock, SOL_SOCKET, SO_SNDBUF, (void *)&opt, oplen);
    setsockopt(tcp_sock, SOL_SOCKET, SO_RCVBUF, (void *)&opt, oplen);

    getsockopt(tcp_sock, SOL_SOCKET, SO_SNDBUF, (void *)&opt, &oplen);
    printf("SET : %d\n", opt);
    getsockopt(udp_sock, SOL_SOCKET, SO_RCVBUF, (void *)&opt, &oplen);
    printf("GET : %d\n", opt);

    return 0;
}
