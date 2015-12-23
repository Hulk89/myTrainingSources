#include <iostream>
#include <fstream>
#include <sstream>

using namespace::std;

int     countPart;
int     countRepl;

bool isTherePart( char* replName, char** partName )
{
    cout << partName << endl;
    int i = 0;
    
    cout << "GG" << endl;
    return false;
}


int main()
{
    char    partName[10000][60];
    char    replPartName[10000][60];
    int     i,j;
    char    dummy[60];
    char    replName[60];

    string  line;

    ifstream replFile( "ReplPart" );    
    ifstream partFile( "Part" );


    i = j = 0;

    while ( getline( partFile, line ) )
    {
        istringstream iss( line );
        if ( !( iss >> dummy >> dummy >> dummy >> dummy >> partName[i] >> dummy >> dummy >> dummy) )
        {
        }
        i++;
    }

    while ( getline( replFile, line ) )
    {
        istringstream iss( line );
        if ( !( iss >> replName >> dummy >> dummy >> dummy >> replPartName[j] >> dummy >> dummy >> dummy) )
        {
        }
        if ( strcmp( replName, "PROOF" ) == 0 )
        {
            j++;
        }
    }

    countPart = i;
    countRepl = j;

    i = j = 0;
    
    cout << countPart << endl;
    cout << countRepl << endl;

    bool isExist;
    for ( j = 0 ; j < countRepl ; j++ )
    {
        isExist = false;

        for ( i = 0 ; i < countPart ; i++ )
        {
            if ( strcmp( replPartName[j], partName[i] ) == 0 )
            {
                isExist = true;
                break;
            }
        }

        if ( isExist != true )
        {
            cout << replPartName[j] << endl;
        }
    }

    return 0;
}
