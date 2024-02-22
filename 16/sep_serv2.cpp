/*分离I/O 在FILE* 指针上，指针fdopen() 根据套接字的文件描述符产生
针对任何一个FILE* 指针调用fclose() 函数都会关闭文件描述付
所以第一步是复制文件描述符 ，只有销毁所有的文件描述符之后才能销毁相关的套接字

第二步
复制文件描述符后“流”的分离
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define BUF_SIZE 1024

int main(int argc,char *argv[])
{
    int serv_sock,clnt_sock;
    FILE* readfp;
    FILE* writefp;

    struct sockaddr_in serv_adr,clnt_adr;
    socklen_t clnt_adr_sz;
    char buf[BUF_SIZE]{0};

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));
    bind(serv_sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr));
    listen(serv_sock, 5);
    clnt_adr_sz = sizeof(clnt_adr);
    clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_adr, &clnt_adr_sz);

    readfp = fdopen(clnt_sock, "r");
    writefp = fdopen(dup(clnt_sock), "w"); //复制文件描述符,针对复制的文件描述符生成了FILE* 指针

    fputs("FROM SERVER: Hi~ client? \n", writefp);
    fputs("I love all of the world \n", writefp);
    fputs("You are awesome! \n", writefp);
    fflush(writefp);

    shutdown(fileno(writefp),SHUT_WR);
    fclose(writefp);

    fgets(buf, sizeof(buf), readfp);
    fputs(buf, stdout);
    fclose(readfp);
    return 0;
}