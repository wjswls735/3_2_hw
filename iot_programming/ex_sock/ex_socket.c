#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
int main()
{
    int fd1, fd2, sd1, sd2;

    fd1 = open("/etc/passwd", O_RDONLY);
    printf("/etc/passwd's file descirptor : %d \n", fd1);

    sd1 = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    printf("TCP socket descirptor : %d\n", sd1);

    sd2 = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    printf("UDP socket descriptor : %d\n", sd2);

    close(fd1);

    fd2 = open("/etc/hosts", O_RDONLY);
    printf("/etc/hosts's file descriptor : %d\n", fd2);

    close(sd1);
    close(sd2);
    close(fd2);
    return 0;
}
