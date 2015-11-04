#include <iostream>
#include <fstream>
using namespace std;


bool* picnic ( bool* aFriendSet, int i, int j );


int main( int argc, char* argv[] )
{
    int   sNumStudent;
    int   sNumCase;
    int   sNumFriend;
    bool* sFriendSet;   // Friend list
    int   i;

    ifstream textFile;
    string   line; 

    //error checking
    if ( argc < 2 )
    {
        cerr << "Usage : ./Picnic example.txt" << endl;
    }

    textFile.open( argv[1] );
    
    getline( textFile,line );
    
    sscanf( line.c_str(), "%d", &sNumCase );

    cout << "The number of case is : " << sNumCase << endl;


    for ( i = 0 ; i < sNumCase ; i++ )
    {
        getline( textFile,line );
        sscanf( line.c_str(), "%d %d", &sNumStudent, &sNumFriend );

        cout << "The number of Student is : " << sNumStudent <<
                "\nThe number of FriendSet is : " << sNumFriend << endl;
        //There will be actual logic.
        


    }

    textFile.close();

    return 0;
}    
