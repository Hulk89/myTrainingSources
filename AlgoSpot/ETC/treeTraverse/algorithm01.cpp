#include <iostream>
#include <vector>
#include <fstream>
#include <string>

//#define DEBUG

using namespace::std;

typedef struct node 
{
    vector<node*>   mChildNode;
    int             mValue;
    int             mNumNode;
} node;

bool gIsNeedRemove = false;

void printNode( vector<node> &aNodeArr )
{
    for ( vector<node>::iterator it = aNodeArr.begin() ;
          it != aNodeArr.end() ;
          ++it )
        {
            cout << "mNumNode : " << it->mNumNode << endl;
            cout << "mValue: " << it->mValue<< endl;
            cout << "child Node : " << endl;
            for ( vector<node*>::iterator it2 = it->mChildNode.begin() ;
                  it2 != it->mChildNode.end() ;
                  ++it2 )
            {
                cout << (*it2)->mNumNode << " ";
            }
            cout << endl;
        }
}

int removeParent( node &aNode, int aParentNum )
{
    int     i = 0;
    node   *sNode;

    for ( i = 0 ; i < aNode.mChildNode.size() ; i++ )  
    {
        sNode = (node*)aNode.mChildNode.at(i);
        if ( sNode->mNumNode == aParentNum )
        {
            aNode.mChildNode.erase( aNode.mChildNode.begin() + i );
            break;
        }
    }

    for ( i = 0 ; i < aNode.mChildNode.size() ; i++ )  
    {
        sNode = (node*)aNode.mChildNode.at(i);
        removeParent( *sNode, aNode.mNumNode );
    }
}

void update( vector<node> &aNodeArr,
             int           aIndex, 
             int           aIncreaseValue )
{
    aNodeArr.at( aIndex-1 ).mValue += aIncreaseValue;
    return;
}

int sumWithRoot( node &aNode )
{
    int sSumValue = aNode.mValue; 
    for ( vector<node*>::iterator it = aNode.mChildNode.begin() ;
          it != aNode.mChildNode.end() ;
          ++it )
    {
        sSumValue += sumWithRoot( **it );
    }
    return sSumValue;
}

int sum( vector<node> &aNodeArr,
         int           aIndex )
{
    return sumWithRoot( aNodeArr.at( aIndex-1 ) );
}

int processString( vector<node> &aNodeArr,
                   char*         aLineCstr,
                   int           aRoot )
{
    string sString( aLineCstr );
    string sDel = " ";
    size_t sPos = 0;
    string sToken[3];
    int    sCnt = 0;

    while ( (sPos = sString.find( sDel ) ) != string::npos )
    {
        sToken[sCnt++] = sString.substr( 0, sPos );
        sString.erase( 0, sPos + sDel.length() );
    }
    if ( sString.length() != 0 )
    {
        sToken[sCnt++] = sString;
    }

    if ( sCnt == 1 )
    {
        gIsNeedRemove = true;
        return atoi( sToken[0].c_str() );
    }
    else 
    {
        if ( gIsNeedRemove )
        {
            removeParent( aNodeArr.at( aRoot - 1 ),
                          0 );
#ifdef DEBUG
            printNode( aNodeArr ); 
#endif
            gIsNeedRemove = false;
        }
        if ( sToken[0].compare("sum") == 0 )
        {
            cout << sum( aNodeArr, atoi( sToken[1].c_str() ) ) << endl;
        }
        else if ( sToken[0].compare("update") == 0 )
        {
            update( aNodeArr,
                    atoi( sToken[1].c_str() ),
                    atoi( sToken[2].c_str() ) );
        }
        else
        {
            int sNum1, sNum2;
            sNum1 = atoi( sToken[0].c_str() );
            sNum2 = atoi( sToken[1].c_str() );
            
            aNodeArr.at( sNum1-1 ).mChildNode.push_back( &(aNodeArr.at( sNum2-1 ) ) );
            aNodeArr.at( sNum2-1 ).mChildNode.push_back( &(aNodeArr.at( sNum1-1 ) ) );
        }
    }
    return 0;
}

int main( int argc, char* argv[] )
{
    int          sNumNode, sRoot;
    vector<node> sNodeArr;
    int          i;
    node         sTmpNode;
    char         sLineStr[1024];

    if ( argc != 2 )
    {
        cout << "Usage : <binary> <file>" << endl;
    }
    else { /* Nothing to do */ } 
    
    ifstream  sInputStream( argv[1] );

    // 1. get the number of node and root node number.
    sInputStream >> sNumNode;
    sInputStream >> sRoot;

    // 2. initialize node with value
    for ( i = 0 ; i < sNumNode ; i++ )
    {
        sInputStream >> sTmpNode.mValue;    
        sTmpNode.mNumNode = i + 1;
        sNodeArr.push_back( sTmpNode );
    }
    sInputStream.getline( sLineStr, 1024 );

    // 3. process string
    while ( 1 )
    {
        sInputStream.getline( sLineStr, 1024 );
        if ( sInputStream.eof() )
        {
            break;
        }
        processString( sNodeArr, sLineStr, sRoot );
    }

    return 0;
}
