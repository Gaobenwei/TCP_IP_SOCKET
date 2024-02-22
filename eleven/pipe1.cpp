#include<stdio.h>
#include<unistd.h>
#define BUF_SIZE 30

int main(int argc,char *argv[])
{
    int fds[2]{-1,-1};
    int fds_[2]{-1,-1};
    char str[]{"who are you?"};
    char buf[BUF_SIZE]{};
    char buf_[BUF_SIZE]{};
    pid_t pid;
    pipe(fds);
    pipe(fds_);
    pid=fork();
    if(pid==0)
    {
        write(fds[1],str,sizeof(str));
        read(fds_[0],buf_,BUF_SIZE);
        printf("this is child proc : %s\n",buf_);
    }
    else
    {
        read(fds[0],buf,BUF_SIZE);
        printf("this is parent proc : %s\n",buf);

        write(fds_[1],"fuck fuck\n",11);
        // puts(buf);
    }
    return 0;
}