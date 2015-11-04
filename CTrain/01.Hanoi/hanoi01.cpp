#include <stdio.h>
#include <stdlib.h>


void hanoi( char src, char tmp, char goal, int n )
{
    if ( n == 1 )
    {
        printf( "%c -> %c\n", src, goal );
        return;
    }
    hanoi( src, goal, tmp, n-1 );
    printf( "%c -> %c\n", src, goal );
    hanoi( tmp, src, goal, n-1 );
}


int main( int argc, char *argv[] )
{
    int n;
    int i =0;
    
    printf( "argc = %d\n", argc );
    for ( i = 0 ; i < argc ; i++ )
    {
        printf( "argv[%d] = %s\n", i, argv[i] );
    }

    n = atoi(argv[1]);
    hanoi('A','B','C',n);

    return 0;
}
