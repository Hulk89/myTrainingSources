#include <stdio.h>
#include <stdlib.h>
// 배열을 사용하는 예제

int *array[3];
int arrayIndex[3];

void hanoi( int src, int tmp, int goal, int n )
{
    int i = 0;
    int j = 0;

    char chip[3];

    if ( n == 1 )
    {
        //printf( "%c -> %c\n", src, goal );
        arrayIndex[src] -= 1;
        arrayIndex[goal] += 1;
        for ( i = n-1 ; i >= 0 ; i-- )
        {
            for ( j = 0 ; j < 3 ; j++ )
            {
                if ( arrayIndex[j] >= i )
                {
                    chip[j] = 'M';
                }
                else
                {
                    chip[j] = '0';
                }
            }
            printf( "%c | %c | %c\n",chip[0],chip[1],chip[2] );
        }
        printf("-------------\n");
        return;
    }
    hanoi( src, goal, tmp, n-1 );
    //printf( "%c -> %c\n", src, goal );
    arrayIndex[src] -= 1;
    arrayIndex[goal] += 1;
    for ( i = n-1 ; i >= 0 ; i-- )
    {
        for ( j = 0 ; j < 3 ; j++ )
        {
            if ( arrayIndex[j] >= i )
            {
                chip[j] = 'M';
            }
            else
            {
                chip[j] = '0';
            }
        }
        printf( "%c | %c | %c\n",chip[0],chip[1],chip[2] );
    }
    printf("-------------\n");
    hanoi( tmp, src, goal, n-1 );
}


int main( int argc, char *argv[] )
{
    int n;
    int i = 0;
    
    printf( "argc = %d\n", argc );
    for ( i = 0 ; i < argc ; i++ )
    {
        printf( "argv[%d] = %s\n", i, argv[i] );
    }

    n = atoi(argv[1]);
///////////////////////////////////////////////////////
    for ( i = 0 ; i < 3 ; i++ )
    {
        array[i] = (int*)malloc( sizeof( int ) * n );
    }
    arrayIndex[0] = n-1;
    arrayIndex[1] = -1;
    arrayIndex[2] = -1;
    
    hanoi( 0, 1, 2, n);

    return 0;
}
