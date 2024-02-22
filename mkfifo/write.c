#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char * argv[]){
    if (argc != 2){
        printf("./a.out fifoname\n");
        return -1;
    }
    //若当前目录有一个myfifo文件
    //打开FIFO文件
    int fd = open(argv[1], O_WRONLY);
    //写
    char buf[256];
    int num = 1;
    while(1){
        memset(buf, 0x00, sizeof(buf));
        sprintf(buf, "xiaoming%04d", num++);
        write(fd, buf, strlen(buf));
        sleep(1);
	}
    //关闭
    close(fd);
    return 0;
}
