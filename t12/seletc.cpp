#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/select.h>
#define BUF_SIZE 30

int main(int argc,char* argv[])
{
    fd_set reads,temps;
    int result,str_len;
    char buf[BUF_SIZE]{""};
    struct timeval timeout;

    //初始化
    FD_ZERO(&reads);
    FD_SET(0,&reads); //将文件描述符0对应位设置为1.即需要监视标准输入的变化

    // timeout.tv_sec=5;
    // timeout.tv_usec=5000;

    while (1)
    {
        temps=reads; //调用select后，除了发生变化的文件描述符对应位之外，其余的都将初始化为0，这里保存了初始状态
        timeout.tv_sec=5;
        timeout.tv_usec=0;//调用select函数后，timeval的成员会变化，每次调用select之前。都要初始化timeval
        result=select(1,&temps,NULL,NULL,&timeout);
        if (result==-1)
        {
            puts("select () error!");
            break;
        }
        else if (result==0)
        {
            puts("time out!");
            continue;
        }
        else
        {
            //result>0,证明有发生变化事件的文件描述符
            if(FD_ISSET(0,&temps)) //判断
            {
                str_len=read(0,buf,BUF_SIZE);
                buf[str_len]='\0';
                printf("message form 0 :%s\n",buf); 
            }
        }
        
        
    }
    return 0;
}