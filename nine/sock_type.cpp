#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
void error_handling(char *message);

int main(int argc, char *argv[])
{
    int tcp_sock, udp_sock;
    int sock_type;
    socklen_t optlen;
    int state;

    optlen = sizeof(sock_type);
    tcp_sock = socket(PF_INET, SOCK_STREAM, 0);
    udp_sock = socket(PF_INET, SOCK_DGRAM, 0);
    printf("SOCK_STREAM: %d\n", SOCK_STREAM);
    printf("SOCK_DGRAM: %d\n", SOCK_DGRAM);

    state=getsockopt(tcp_sock,SOL_SOCKET,SO_TYPE,(void*)&sock_type,&optlen);

    // state = getsockopt(tcp_sock, SOL_SOCKET, SO_TYPE, (void *)&sock_type, &optlen);
    if (state)
        error_handling("getsockopt() error");
    printf("Socket type one: %d \n", sock_type);
    optlen=0;
    state = getsockopt(udp_sock, SOL_SOCKET, SO_TYPE, (void *)&sock_type, &optlen);
    if (state)
        error_handling("getsockopt() error");
    printf("Socket type two: %d \n", sock_type);

    int val{0};
    socklen_t len{sizeof(val)};

    state=getsockopt(tcp_sock,SOL_SOCKET,SO_SNDBUF,(void*)&val,&len);
    printf("Socket SO_SNDBUF: %d \n", val);
    val=1024*16;
    setsockopt(tcp_sock,SOL_SOCKET,SO_SNDBUF,(const void*)&val,len);
    state=getsockopt(tcp_sock,SOL_SOCKET,SO_SNDBUF,(void*)&val,&len);
    printf("Socket SO_SNDBUF*************: %d \n", val);
    return 0;
}
void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}