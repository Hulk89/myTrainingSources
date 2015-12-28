#include <iostream>
#include <math.h>
using namespace std;

#define NOT_CALCULATED ( -1 )
#define DENOM          ( 1000000007 )

long long int array[101];
long long int allArr[101];

long long int multiply( long long int a, long long int b )
{
    int i;
    long long int sResult = 0;

    for ( i = 0 ; i < b ; i++ )
    {
        sResult += a;
        
        if ( sResult >= DENOM )
        {
            sResult = sResult % DENOM;
        }
    }

    return sResult;
}

long long int AllTiling( int aNumOfBlock )
{
    long long int a, b;

    if ( allArr[aNumOfBlock] != NOT_CALCULATED )
        return allArr[aNumOfBlock];
    
    if ( aNumOfBlock % 2 == 0 )
    {
        a = AllTiling( aNumOfBlock/2 );
        b = AllTiling( aNumOfBlock/2-1 );

        allArr[aNumOfBlock] = ( multiply( a , a ) + multiply( b, b ) ) % DENOM;

        return allArr[aNumOfBlock];
    }
    else
    {
        allArr[aNumOfBlock] = ( AllTiling( aNumOfBlock - 1 ) +
                ( 2 * ( multiply( AllTiling( (aNumOfBlock-3)/2 ), 
                                  AllTiling( (aNumOfBlock-1)/2 ) )
                                % DENOM ) - 1
                     ) % DENOM ) % DENOM;

        return allArr[aNumOfBlock];
    }
}

long long int AsymTiling( int aNumOfBlock )
{
    long long int a,b;

    if ( array[aNumOfBlock] != NOT_CALCULATED )
        return array[aNumOfBlock];
    
    if ( aNumOfBlock % 2 == 0 )
    {
        a = AllTiling( aNumOfBlock/2 );
        b = AllTiling( aNumOfBlock/2 - 1 );

        array[aNumOfBlock] = ( multiply( a, a-1 )  + multiply( b, b-1 )  ) % DENOM;
        return array[aNumOfBlock];
    }
    else
    {
        array[aNumOfBlock] = ( AsymTiling( aNumOfBlock - 1 ) + 
                 ( 2 * multiply( AllTiling( (aNumOfBlock-3)/2 ), 
                                 AllTiling( (aNumOfBlock-1)/2 ) ) % DENOM ) ) % DENOM ;
        return array[aNumOfBlock];
    }
}

int main()
{
    int sNumOfTestcase;
    uint sResult;
    int sNumOfBlock;
    int i;
    std::ios::sync_with_stdio(false);

/* Initialization */
    for ( i = 0 ; i <= 100 ; i++ )
    {
        array[i] = NOT_CALCULATED;
        allArr[i] = NOT_CALCULATED;
    }
    array[1] = 0;
    array[2] = 0;
    allArr[1] = 1;
    allArr[2] = 2;
    allArr[3] = 3;

///////////////////////////////////////

    cin >> sNumOfTestcase;

    for ( i = 0 ; i < sNumOfTestcase ; i++ )
    {
        cin >> sNumOfBlock;

        sResult = AsymTiling( sNumOfBlock );

        cout << sResult << endl;

    }

    return 0;
}
