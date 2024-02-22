#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
struct stu{
        int which ;
        char buf[1024] ;
};

int main( int argc , char **argv ) {
    // int shm_id=shmget(ftok(".",2),sizeof(struct stu),IPC_CREAT | 0666);
    // if(shm_id==-1)
    // {
    //     printf( "create shm fail! -- %d\n" , shm_id ) ;
    //     exit(0) ;
    // }
    // printf("create share memory:%d good \n",shm_id);
    // struct stu* shm_addr=(struct stu*)shmat(shm_id,NULL,0);
    // if(shm_addr==nullptr)
    // {
    //             printf( "link shm fail!" ) ;
    //             exit( 0 ) ;
    // }
    // printf("link shm succeed\n");

    // char buf[1024]{};
    // shm_addr->which=0;
    // while (1)
    // {
    //     if(!shm_addr->which)
    //     {
    //         printf("Pleas input :") ;
    //         fgets( buf,1024,stdin ) ;
    //         strcpy( shm_addr->buf,buf ) ;
    //         shm_addr->which = 1 ;
    //         if( 0==strncmp(buf,"end",3) ) {
    //             break ;
    //         }
    //     }
    // }
    
    // printf("break\n") ;
    //     if( !shmdt(shm_addr) ) {//取消映射
    //             printf( "shm link delete succeed !\n" ) ;
    //     }
    //     shmctl( shm_id , IPC_RMID , 0 ) ;

        //创建共享内存
        int shm_id = shmget( ftok(".",2),sizeof( struct stu ),IPC_CREAT|0666 ) ;
        if( -1==shm_id ) {
                printf( "create shm fail! -- %d\n" , shm_id ) ;
                exit(0) ;
        }
        printf( "create shm succeed !--%d\n" , shm_id ) ;
        /*shm creae : up 映射共享内存*/
        struct stu *shm_addr = (struct stu*)shmat( shm_id , NULL , 0 ) ;
        if( (void*)-1==shm_addr ) {
                printf( "link shm fail!" ) ;
                exit( 0 ) ;
        }
        printf( "link shm succeed!\n" ) ;
        /*shm link : up  在内存写东西*/
        char buf[1024] ;
        shm_addr->which = 0 ;
        while( 1 ){
                if( !shm_addr->which ) {
                        printf("Pleas input :") ;
                        fgets( buf,1024,stdin ) ;
                        strcpy( shm_addr->buf,buf ) ;
                        shm_addr->which = 1 ;
                        if( 0==strncmp(buf,"end",3) ) {
                                break ;
                        }
                }
        }
        printf("break\n") ;
        if( !shmdt(shm_addr) ) {//取消映射
                printf( "shm link delete succeed !\n" ) ;
        }
        shmctl( shm_id , IPC_RMID , 0 ) ;

        return 0 ;
}
