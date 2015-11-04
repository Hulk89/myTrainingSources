#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

void sig_int( int signo );
void sig_usr( int signo );

int main()
{
    int i = 0;
    struct sigaction intsig, usrsig;

    printf("PID : %d\n", getpid() );
    // SIGUSR signal handling
    usrsig.sa_handler = sig_usr;
    sigemptyset(&usrsig.sa_mask);
    usrsig.sa_flags = 0;

    if ( sigaction( SIGUSR1, &usrsig, 0 ) == -1 )
    {
        printf( "signal( SIGUSR ) error" );
        return -1;
    }

    // SIGUSR2 signal handling
    usrsig.sa_handler = sig_usr;
    sigemptyset(&usrsig.sa_mask);
    usrsig.sa_flags = 0;

    if ( sigaction( SIGUSR2, &usrsig, 0 ) == -1 )
    {
        printf( "signal( SIGUSR2 ) error" );
        return -1;
    }

    //SIGINT (CTRL+C) handling
    intsig.sa_handler = sig_int;
    sigemptyset(&intsig.sa_mask);
    intsig.sa_flags = 0;

    if ( sigaction( SIGINT, &intsig, 0 ) == -1 )
    {
        printf( "signal( SIGINT ) error" );
        return -1;
    }

    while ( 1 )
    {
        printf( "%d\n", i );
        i++;
        sleep(1);
    }
    return 0;
}

void sig_int( int signo )
{
    sigset_t sigset, oldset;
    int i = 0;
    sigemptyset( &oldset );

    sigemptyset( &sigset );
    sigaddset( &sigset, SIGUSR2 );
    sigaddset( &sigset, SIGUSR1 );

    if ( sigprocmask( SIG_BLOCK, &sigset, &oldset ) < 0 )
    {
        printf( "sigprocmask %d error \n", signo );
    }

    sigemptyset( &sigset );
    sigaddset( &sigset, SIGINT );

    if ( sigprocmask( SIG_UNBLOCK, &sigset, &oldset ) < 0 )
    {
        printf( "sigprocmask %d error \n", signo );
    }

    printf( "sig_int\n" );
    for (i = 0 ; i < 10 ; i++ )
    {
        printf( "%d\n", 1000-i );
        sleep(1);
    }
}


void sig_usr( int signo )
{
    printf( "sig_usr %d\n", signo );
}
