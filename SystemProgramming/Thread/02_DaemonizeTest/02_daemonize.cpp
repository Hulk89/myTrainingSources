#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>


#define MAX_LEN 20

bool isRunning;

struct dataForThread {
    int id;
    char str[MAX_LEN];
};

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

void* funcForThread ( void* data )
{
    int             i = 0;
    dataForThread   me = *((dataForThread*)data);

    int serv_sock;
    int clnt_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    int      option = 1;


    char message[] = "Hello World!";
    
    
    serv_sock = socket( PF_INET, SOCK_STREAM, 0 ); 
    if ( serv_sock == -1 ) 
        error_handling( "socket() error" );
    
    memset( &serv_addr, 0, sizeof( serv_addr ) );
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl( INADDR_ANY );
    serv_addr.sin_port=htons(atoi(me.str));
    // enable Reuse Address and port
    setsockopt( serv_sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof( option ) );
    
    if( bind( serv_sock, (struct sockaddr*) &serv_addr, sizeof( serv_addr ) ) == -1 )
        error_handling( "bind() error" ); 
    
    if( listen( serv_sock, 5 ) == -1 )
        error_handling( "listen() error" );
    
    clnt_addr_size = sizeof( clnt_addr );  

    while ( 1 ) 
    {   
        clnt_sock=accept( serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size );
        if( clnt_sock==-1 )
            error_handling( "accept() error" );  
        
        write(clnt_sock, message, sizeof(message));
        close( clnt_sock );  

        isRunning = false;
        break;
    }   

    close( serv_sock );

    pthread_exit( NULL );
}


int main ( int argc, char* argv[] )
{
    int             thread_id;  /* 쓰레드 ID */
    pthread_t       p_thread;   /* thread 구조체 */
    dataForThread   another_thread;    
    pid_t           pid;        /* daemonized process ID */

    /* port checking */
    if ( argc != 2 )
    {
        printf( "usage : daemonize <portNo>\n" );
        exit( EXIT_SUCCESS );
    }

    isRunning = true;


    pid = fork();

    if ( pid < 0 )
    {
        exit( EXIT_FAILURE );
    }
    if ( pid > 0 )
    {
        exit( EXIT_SUCCESS );
    }
    
    umask( 0 );

    close( STDIN_FILENO );
    //close( STDERR_FILENO );
    //close( STDOUT_FILENO );




    /* thread argument setting */
    memset( &another_thread, 0x00, sizeof( dataForThread ) );
    another_thread.id = 1;
    strcpy( another_thread.str, argv[1] );
    thread_id = pthread_create( &p_thread, NULL, funcForThread, (void*)&another_thread);



    while ( isRunning == true )
    {
        printf( "Daemon Process is alive.\n" );
        sleep( 10 );
    }

    return 0;
}


