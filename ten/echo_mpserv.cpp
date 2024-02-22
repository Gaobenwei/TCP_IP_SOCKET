#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
void error_handling(char *message);
void read_childproc(int sig);

void read_childproc(int sig)
{
    pid_t pid;
    int status{};
    pid=waitpid(-1,&status,WNOHANG);
    printf("remove proc id: %d \n",pid);
}

void error_handling(char *message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}

int main(int argc,char* argv[])
{
    int serv_sock,clnt_sock;
    struct sockaddr_in serv_addr,clnt_addr;

    pid_t pid;
    struct sigaction act;
    socklen_t adr_sz;
    int str_len,state;
    char buf[BUF_SIZE];
        if (argc != 2)
    {
        printf("Usgae : %s <port>\n", argv[0]);
        exit(1);
    }

    act.sa_handler=read_childproc;
    sigemptyset(&act.sa_mask);
    act.sa_flags=0;
    state=sigaction(SIGCHLD,&act,0);
    serv_sock=socket(PF_INET,SOCK_STREAM,0);
    memset(&serv_addr,0,sizeof(serv_addr));

    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_addr.sin_port=htons(atoi(argv[1]));

    if(bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))==-1)
    {
        error_handling("bind() error");
    }
    if(listen(serv_sock,5)==-1)
    {
        error_handling("listen() error");
    }

    int count{0};
    for(int i=0;i<3;++i)
    {
        adr_sz=sizeof(clnt_addr);
        clnt_sock=accept(serv_sock,(struct sockaddr*)&clnt_addr,&adr_sz);
        if(clnt_sock==-1)
        continue;
        else
        {
            puts("new client connected ...");
            count++;
        }
            

        pid=fork();
        if(pid==-1)
        {
            close(clnt_sock);
            continue;
        }
        if(pid==0)
        {
            close(serv_sock);
            while((str_len=read(clnt_sock,buf,BUF_SIZE))!=0)
            {
                write(clnt_sock,buf,str_len);
            }
            close(clnt_sock);
            puts("client disconnected ...");
            return 0;
        }
        else
        {
            sleep(2);
            close(clnt_sock);
            // if(count>2) //有些许问题
            // {
            //     break;
            // }
        }
    }
    close(serv_sock);

    return 0;
}