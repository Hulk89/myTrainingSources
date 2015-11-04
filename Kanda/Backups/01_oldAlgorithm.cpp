#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>

#define VELOCITY        ( 1 )
#define MAX_X           ( 1000 )
#define MAX_Y           ( 1000 )
#define MAX_TIME        ( 1000 )
#define MAX_EXEC_TIME   ( 2000 )
#define NUM_PARCEL      ( 10 )
#define RADIUS          ( 4 )
#define NULL_RIDER      ( -1 )


//#define DEBUG 1
#define UNITTEST 1
using namespace::std;

/******** struct Definition *******/
typedef struct ikuPoint
{
    float x;
    float y;
    int   mRider;
} ikuPoint;

float length( ikuPoint aPos )
{
    float sResult;
    sResult = sqrt(aPos.x*aPos.x + aPos.y*aPos.y);

    return sResult;
}

float length( ikuPoint aPos1, ikuPoint aPos2 )
{
    ikuPoint sDiff;
    sDiff.x = aPos1.x - aPos2.x;
    sDiff.y = aPos1.y - aPos2.y;

    return length( sDiff );
}

typedef struct ikuInfo
{
    ikuPoint mStart;
    ikuPoint mEnd;
    int      mReqTime;
    int      mArrivalTime;
} ikuInfo;

void randomGen( ikuInfo * aIkuInfo )
{
    int i;

    srand( time(NULL) );

    for ( i = 0 ; i < NUM_PARCEL ; i++ )
    {
        aIkuInfo[i].mStart.x     = rand() % MAX_X;
        aIkuInfo[i].mStart.y     = rand() % MAX_Y;
        aIkuInfo[i].mStart.mRider= NULL_RIDER;
        aIkuInfo[i].mEnd.x       = rand() % MAX_X;
        aIkuInfo[i].mEnd.y       = rand() % MAX_Y;
        aIkuInfo[i].mEnd.mRider = NULL_RIDER;
        aIkuInfo[i].mReqTime     = rand() % MAX_TIME;
    } 
}
void printPos( ikuPoint  a )
{
    cout << "( " << a.x << ", " << a.y << ") rider : " <<
            a.mRider << endl;
}

void print( ikuInfo a )
{
    cout << "startPos : (" << a.mStart.x  << ", "
         << a.mStart.y  << ") endPos : ("
         << a.mEnd.x    << ", "
         << a.mEnd.y    << ") Time = "
         << a.mReqTime;
         
    if ( ( a.mStart.mRider == NULL_RIDER ) ||
         ( a.mEnd.mRider == NULL_RIDER ) )
    {
        cout << " State : Not Delivered" << endl;   
    }
    else
    {
        cout << " State : Delivered" << endl;
    }
}

bool compareTime( ikuInfo a, ikuInfo b ) 
{ 
    return ( a.mReqTime < b.mReqTime ); 
}
//////////////////////////////////////////////////////
/* mNodes[0] : Goal position
 * 
 *
 */
typedef struct ikuRider
{
    ikuPoint               mPos;
    std::vector<ikuPoint*> mNodes;
    int                    mRiderNum;
} ikuRider;

void calculateNextPosition( ikuRider *aRider )
{
    ikuPoint sNewPos;
    ikuPoint sDiffPos;

    if ( !aRider->mNodes.empty() )
    {
        sDiffPos.x = aRider->mNodes.at(0)->x - aRider->mPos.x;
        sDiffPos.y = aRider->mNodes.at(0)->y - aRider->mPos.y;

        if ( length( sDiffPos ) < VELOCITY )
        {
            aRider->mPos.x = aRider->mNodes.at(0)->x;
            aRider->mPos.y = aRider->mNodes.at(0)->y;
            aRider->mNodes.at(0)->mRider = aRider->mRiderNum;
            aRider->mNodes.erase(aRider->mNodes.begin());
        }
        else
        {
            sNewPos.x = aRider->mPos.x + sDiffPos.x / length( sDiffPos ) * VELOCITY;
            sNewPos.y = aRider->mPos.y + sDiffPos.y / length( sDiffPos ) * VELOCITY;
            aRider->mPos.x = sNewPos.x;
            aRider->mPos.y = sNewPos.y;
        }
    }
    else
    {
        /* Nothing to do */
    }
}

std::vector<ikuInfo>::iterator  getClosestInfo( std::vector<ikuInfo> *aCurInfo,
                                                 ikuRider             *aRider,
                                                 int                  *isValid)
{
    std::vector<ikuInfo>::iterator sClosestInfo;
    int  sIsValid = 0;

    for ( std::vector<ikuInfo>::iterator it = aCurInfo->begin() ; 
         it != aCurInfo->end() ;
         ++it )
    {
        if ( it == aCurInfo->begin() )
        {
            sIsValid = 1;
            sClosestInfo = it;
        }
        else
        {
            if ( length( sClosestInfo->mStart, aRider->mPos ) >
                 length( it->mStart, aRider->mPos ) )
            {
                sClosestInfo = it;
            }
            else
            {
                /* Nothing to do */
            }
        }
    }
    *isValid = sIsValid;

    return sClosestInfo;
}

void newAlgorithm( std::vector<ikuInfo> * aCurInfo,
                   std::vector<ikuInfo> * aAllocInfo,
                   ikuRider             * aRider )
{
    /* Nothing to do */    
}

void oldAlgorithm( std::vector<ikuInfo> * aCurInfo,
                   std::vector<ikuInfo> * aAllocInfo,
                   ikuRider             * aRider )
{
    std::vector<ikuInfo>::iterator sClosestInfo;
    int   sIsValid;
    if ( aRider->mNodes.empty() )
    {
        sClosestInfo = getClosestInfo( aCurInfo, aRider, &sIsValid);
        if ( sIsValid != 0 )
        {
            aAllocInfo->push_back(*sClosestInfo);
            aCurInfo->erase(sClosestInfo);

            aRider->mNodes.push_back(&(aAllocInfo->back().mStart));
            aRider->mNodes.push_back(&(aAllocInfo->back().mEnd));
        }
    }
    else
    {
        /* Nothing to do */
    }
    calculateNextPosition( aRider );

}


/********** main Function ***********/
int main()
{
    ikuInfo sIkuInfo[NUM_PARCEL];
    int i;
    int k;

/* Step 1. Generate and sort data set. */
    randomGen(sIkuInfo);
//// Vector
    std::vector<ikuInfo> sParcelInfoArr( sIkuInfo, sIkuInfo + NUM_PARCEL );
    
    std::vector<ikuInfo> sCurInfo;
    std::vector<ikuInfo> sCurInfo2;

    std::vector<ikuInfo> sAllocInfo;
    std::vector<ikuInfo> sAllocInfo2;

/// sorting
    std::sort( sParcelInfoArr.begin(), sParcelInfoArr.end(), compareTime );        
    cout << "parcel contains:" << endl;
    for ( std::vector<ikuInfo>::iterator it = sParcelInfoArr.begin();
          it != sParcelInfoArr.end(); 
          ++it )
    {
        print(*it);
    }

    ikuRider sRider1;
    ikuRider sRider2;

    // initialize rider
    sRider1.mPos.x = sRider2.mPos.x = rand() % MAX_X; 
    sRider1.mPos.y = sRider2.mPos.y = rand() % MAX_Y; 
    sRider1.mRiderNum = 1;
    sRider2.mRiderNum = 2;

    //print riders position
    cout << "Riders initial position : ( " << sRider1.mPos.x 
                                   << ", " << sRider1.mPos.y 
                                   << " )" << endl;

#ifdef UNITTEST
    std::vector<ikuInfo>::iterator sClosestInfo;
    int a;
    sClosestInfo = getClosestInfo( &sParcelInfoArr, &sRider1, &a );
    print( *sClosestInfo );
#endif

/* Step 2. Do while end of EXEC_TIME*/
    for ( i = 0 ; i < MAX_EXEC_TIME ; i ++ )
    {
        /* sCurInfo <== not allocced parcel in current time*/
        /* sAllocInfo <== allocced Parcel in current time */

        while ( !sParcelInfoArr.empty() )
        {
            if ( sParcelInfoArr.front().mReqTime <= i )
            {
                /* sCurInfo, sCurInfo2 <- sParcelInfoArr ! */
                sCurInfo.push_back( sParcelInfoArr.front() );
                sCurInfo2.push_back( sParcelInfoArr.front() );
                sParcelInfoArr.erase( sParcelInfoArr.begin() );
            }
            else
            {
                break;
            }
        }

#ifdef DEBUG
        cout << "CUR_TIME : " << i << "_____________" << endl;
        for ( std::vector<ikuInfo>::iterator it = sCurInfo.begin();
          it != sCurInfo.end(); 
          ++it )
        {
            print(*it);
        }
#endif
    
/* 3. simulate algorithms */

        newAlgorithm( &sCurInfo,
                      &sAllocInfo,
                      &sRider1 );

        oldAlgorithm( &sCurInfo2, 
                      &sAllocInfo2,
                      &sRider2 );
    }

    cout << "-------- Rider2 Result ---------" << endl;
    for ( std::vector<ikuInfo>::iterator it = sAllocInfo2.begin();
          it != sAllocInfo2.end(); 
          ++it )
    {
        print(*it);
    }
    return 0;
}
