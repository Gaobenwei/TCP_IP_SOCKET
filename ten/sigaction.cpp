#include <stdio.h>
#include <unistd.h>
#include <signal.h>

// void timeout(int sig)
// {
//     if (sig == SIGALRM)
//         puts("Time out!");
//     alarm(2);
// }

void timeout(int sig)
{
    if(sig==SIGALRM)
    {
        puts("Time out!");
    }
    alarm(2);
}

int main(int argc, char *argv[])
{
    int i;
    // struct sigaction act;
    // act.sa_handler = timeout;    //保存函数指针
    // sigemptyset(&act.sa_mask);   //将 sa_mask 函数的所有位初始化成0
    // act.sa_flags = 0;            //sa_flags 同样初始化成 0
    // sigaction(SIGALRM, &act, 0); //注册 SIGALRM 信号的处理器。

    struct sigaction act;
    act.sa_handler=timeout;
    sigemptyset(&act.sa_mask);
    act.sa_flags=0;
    sigaction(SIGALRM,&act,0);
    alarm(2); //2 秒后发生 SIGALRM 信号

    for (int i = 0; i < 3; i++)
    {
        puts("wait...");
        sleep(100);
    }
    return 0;
}