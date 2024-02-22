#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void ctrl_handling(int sig);
void ctrl_handling(int sig)
{
    char c{};
    if(sig==SIGINT)
    {
        fputs("Do you want to exit(Y to exit)?", stdout);
        scanf("%c",&c);
        if(c=='y'||c=='Y')
        {
            exit(1);
        }
    }
}

int main(int argc,char *argv[])
{
    struct sigaction act;
    act.sa_handler=ctrl_handling;
    sigemptyset(&act.sa_mask);
    act.sa_flags=0;
    sigaction(SIGINT,&act,0);

    while(1)
    {
        sleep(1);
        printf("hellp\n");
    }
    return 0;


}