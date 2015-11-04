#include <iostream>
#include <string.h>

using namespace std;

#define MAXLEN (1001)

char gOriginal[MAXLEN];
char gResult[MAXLEN];

int getNextPosition( int aStart, int aEnd )
{
    int sPtr;
    int sCount;

    sCount = 4;

    switch ( gResult[aStart] )
    {
        case 'x':
            for ( sPtr = aStart + 1 ; sPtr <= aStart + sCount ; sPtr++ )
            {
                if ( gResult[sPtr] == 'x' )
                {
                    sCount += 4;
                }
                else
                {
                    /* Nothing to do */
                }
            }
            return sPtr;
        case 'b':
        case 'w':
            return aStart + 1;
        default:
            break;
    }
    return aStart;
}

void reverseQuadTree( int aStart, int aEnd )
{
    int  s1st, s2nd, s3rd;
    char sTemp[MAXLEN] = { 0, };

    if ( aStart == aEnd )
    {
        /* Nothing to do */
    }
    else
    {
        s1st = getNextPosition( aStart + 1, aEnd );
        s2nd = getNextPosition( s1st, aEnd );
        s3rd = getNextPosition( s2nd, aEnd );

        reverseQuadTree( aStart + 1, s1st - 1 );
        reverseQuadTree( s1st, s2nd - 1 );
        reverseQuadTree( s2nd, s3rd - 1 );
        reverseQuadTree( s3rd, aEnd );
        
        strncpy( sTemp, 
                 gResult + s2nd, 
                 aEnd - s2nd + 1 );

        strncpy( sTemp + aEnd - s2nd + 1, 
                 gResult + aStart + 1, 
                 s2nd - aStart - 1 );

        strncpy( gResult + aStart + 1,
                 sTemp,
                 aEnd - aStart );
    }
}


void reverseQuadTree()
{
    int sLen;
    int sStart;
    int sEnd;

    sLen = strlen( gOriginal );
    sStart = 0;
    sEnd = sLen - 1;

    strcpy( gResult, gOriginal ); 
    reverseQuadTree( sStart, sEnd );
}

int main()
{
    int sNumOfTestcase;
    int i;
    std::ios::sync_with_stdio(false);

    cin >> sNumOfTestcase;

    for ( i = 0 ; i < sNumOfTestcase ; i++ )
    {
        cin >> gOriginal;

        reverseQuadTree();

        cout << gResult << endl;
    }

    return 0;
}
