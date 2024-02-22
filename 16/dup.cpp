/*分离I/O 在FILE* 指针上，指针fdopen() 根据套接字的文件描述符产生
针对任何一个FILE* 指针调用fclose() 函数都会关闭文件描述付
所以第一步是复制文件描述符 ，只有销毁所有的文件描述符之后才能销毁相关的套接字*/

#include<stdio.h>
#include<unistd.h>

int main(int argc,char* argv[])
{
    int cfd1,cfd2;
    char str1[]{"Hi~ \n"};
    char str2[]{"It is nice day~ \n"};

    cfd1=dup(1);
    cfd2=dup2(cfd1,7);

    printf("fd1=%d , fd2=%d \n", cfd1, cfd2);
    write(cfd1, str1, sizeof(str1));
    write(cfd2, str2, sizeof(str2));

    close(cfd1);
    close(cfd2); //终止复制的文件描述符，但是仍有一个文件描述符
    write(1, str1, sizeof(str1));
    close(1);
    write(1, str2, sizeof(str2)); //无法完成输出
    return 0;
}