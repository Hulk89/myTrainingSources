#include <stdio.h>
#include <string.h>

#define MAX 100

int main()
{
    char buf[100];
    int  len; 
    int  i;

//////////////////////////
    int     operand[10] = { 0, };
    int     opnIdx = 0;
    char    operatorTmp;

////////// input //////////////
    fgets(buf,MAX,stdin);
    //scanf( "%s", buf );

    printf("string : %s\n", buf );
    len = strlen(buf);
///////////////////////////////
    i = 0;

    while ( i < len )
    {
        if ( ( '0' <= buf[i] ) && ( '9' >= buf[i] ) )
        {
            operand[opnIdx] *= 10;
            operand[opnIdx] += ( buf[i] - '0' );
        }
        else
        {
            opnIdx++;
            switch ( buf[i] )
            {
                case '+':   /* fall through */
                case '-':
                case '*':
                    operatorTmp = buf[i];
                    break;
                default:
                    break;
            }
        }
        i++;
    }
    for ( i = 0 ; i < opnIdx ; i++ )
    {
        printf( " %d \n", operand[i] );
    }

    switch ( operatorTmp )
    {
        case '+':
            printf( "result : %d\n", operand[0] + operand[1]);
            break;
        case '-':
            printf( "result : %d\n", operand[0] - operand[1]);
            break;
        case '*':
            printf( "result : %d\n", operand[0] * operand[1]);
            break;
        default:
            break;
    }

    return 0;
}
