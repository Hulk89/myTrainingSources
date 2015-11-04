#include <stdio.h>
#include <pthread.h>
#include <string.h>


#define MAX_LEN 20

struct dataForThread {
    int id;
    char str[MAX_LEN];
};

void*
funcForThread ( void* data )
{
    int             i = 0;
    dataForThread   me = *((dataForThread*)data);

    for ( i = 0 ; i < 10 ; i++ )
    {
        printf( "thread name = %s, thread id = %d, %d\n", me.str, me.id, i );
    }

    pthread_exit( NULL );
}



int main ( int argc, char* argv[] )
{
    int             thread_id;  /* 쓰레드 ID */
    pthread_t       p_thread;   /* thread 구조체 */
    dataForThread   main_thread;
    dataForThread   another_thread;
    
    memset( &main_thread, 0x00, sizeof(dataForThread) );
    memset( &another_thread, 0x00, sizeof(dataForThread) );

    main_thread.id = 1;
    strcpy( main_thread.str, "mainThread" );

    another_thread.id = 2;
    strcpy( another_thread.str, "anotherThread" );

    thread_id = pthread_create( &p_thread, NULL, funcForThread, (void*)&another_thread);

    funcForThread( (void*)&main_thread );

    return 0;
}
