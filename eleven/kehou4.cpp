#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define BUF_SIZE 30

int main(int argc,char *argv[])
{
    int fds1[2]{-1,-1};
    int fds2[2]{-1,-1};

    pipe(fds1);
    pipe(fds2);

    char str1[] = "Do you like cooffee?";
    char str2[] = "I like coffee";
    char str3[] = "I like long legs";
    char * str_arr[] = {str1, str2, str3};
    char buf[BUF_SIZE]{""};
    pid_t pid;
    int i;

    pid=fork();
    if(pid==0)
    {
        for(int i=0;i<3;++i)
        {
            write(fds1[1],str_arr[i],strlen(str_arr[i])+1);
            read(fds2[0],buf,BUF_SIZE);
            printf("child proc message :%s\n",buf);
        }
    }
    else
    {
        for(int i=0;i<3;++i)
        {
            read(fds1[0],buf,BUF_SIZE);
            printf("parent proc message %s\n",buf);
            write(fds2[1],str_arr[i],strlen(str_arr[i])+1);
        }
    }
    return 0;
}