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

        int shm_id = shmget( ftok(".",2),sizeof( struct stu ),IPC_CREAT|0666 ) ;
        if( -1==shm_id ) {
                printf( "create shm fail! -- %d\n" , shm_id ) ;
                exit(0) ;
        }
        printf( "create shm succeed !--%d\n" , shm_id ) ;
        /*shm creae : up*/
        struct stu *shm_addr = static_cast<struct stu*>(shmat( shm_id , NULL , 0 )) ;
        if( (void*)-1==shm_addr ) {
                printf( "link shm fail!" ) ;
                exit( 0 ) ;
        }
        printf( "link shm succeed!\n" ) ;
        /*shm link : up*/
        while( 1 ){
                if( shm_addr->which ) {
                        printf("read is:%s--\n",shm_addr->buf) ;
                        shm_addr->which = 0 ;
                        if( 0==strncmp(shm_addr->buf,"end",3) ) {
                                break ;
                        }
                }
        }
        if( !shmdt(shm_addr) ) {
                printf( "shm link delete succeed !\n" ) ;
        }
        shmctl( shm_id , IPC_RMID , 0 ) ;

        return 0 ;
}
