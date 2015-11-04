#include <iostream>

using namespace std;

#define NOT_CALCULATED ( -1 )
#define MAXCOUNT       ( 10000000 )

int array[101][101];

int merge( int aUpperBlock, int aLowerBlock )
{
    return ( aUpperBlock + aLowerBlock - 1 ); 
}

int getCounts( int aNumOfBlock, int aFirstBlock )
{
    int sSecondBlock;

    if ( array[aNumOfBlock][aFirstBlock] == NOT_CALCULATED )
    {
        array[aNumOfBlock][aFirstBlock] = 0;
        for ( sSecondBlock = 1; sSecondBlock <= aNumOfBlock - aFirstBlock ; sSecondBlock++ )
        {
            array[aNumOfBlock][aFirstBlock] +=  merge( aFirstBlock, sSecondBlock )
                                              * getCounts( aNumOfBlock - aFirstBlock, sSecondBlock );
            array[aNumOfBlock][aFirstBlock] = array[aNumOfBlock][aFirstBlock] % MAXCOUNT;
        }
    }
    else
    {
        /* Nothing to do */
    }

    return array[aNumOfBlock][aFirstBlock];
}

int poly( int aNumOfBlock )
{
    int sMyBlock;
    int sSum = 0;

    sSum = 0;
    // get result from HERE!!
    for ( sMyBlock = 1 ; sMyBlock <= aNumOfBlock ; sMyBlock++ )
    {
        sSum += getCounts( aNumOfBlock, sMyBlock );
        sSum %= MAXCOUNT;
    }
    return sSum;
}

int main()
{
    int sNumOfTestcase;
    int sResult;
    int sNumOfBlock;
    int i,j;
    std::ios::sync_with_stdio(false);

/* Initialization */
    for ( i = 0 ; i <= 100 ; i++ )
        for ( j = 0 ; j <= 100 ; j++ )
            if ( i == 0 || j == 0 )
                array[i][j] = 0;
            else if ( i == j )
                array[i][j] = 1;
            else
                array[i][j] = NOT_CALCULATED;
///////////////////////////////////////
    cin >> sNumOfTestcase;

    for ( i = 0 ; i < sNumOfTestcase ; i++ )
    {
        cin >> sNumOfBlock;

        sResult = poly( sNumOfBlock );

        cout << sResult << endl;

    }

    return 0;
}
