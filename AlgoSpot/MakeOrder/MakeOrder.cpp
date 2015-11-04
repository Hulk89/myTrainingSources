#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int i, j, k;
    int sNumOfTestcase;
    int sNumOfCoder;
    int sNumOfWin;

    int *sRussia = NULL;
    int *sKorea = NULL;

///////////////////////////////////////////////////

    std::ios::sync_with_stdio(false);

    cin >> sNumOfTestcase;

    for ( i = 0 ; i < sNumOfTestcase ; i++ )
    {
        cin >> sNumOfCoder;

        sRussia = (int*)malloc( sizeof(int) * sNumOfCoder );
        sKorea  = (int*)malloc( sizeof(int) * sNumOfCoder );

        for ( j = 0 ; j < sNumOfCoder ; j++ )
            cin >> sRussia[j];
        for ( j = 0 ; j < sNumOfCoder ; j++ )
            cin >> sKorea[j];

        /* code starts here! */
        sNumOfWin = 0;

        sort( sRussia, sRussia + sNumOfCoder );
        sort( sKorea,  sKorea  + sNumOfCoder );

        for ( j = 0, k = 0 ; j < sNumOfCoder ; j++ )
        {
            if ( sKorea[j] >= sRussia[k] )
            {
                sNumOfWin++;
                k++;
            }
            else
            {
                /* Nothing to do */
            }
        }

        cout << sNumOfWin << endl;

        /* end of code */
        free( sRussia );
        free( sKorea  );
    }
    
    return 0;
}
