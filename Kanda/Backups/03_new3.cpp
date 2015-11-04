#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>

#define VELOCITY        ( 7 )
#define MAX_X           ( 1000 )
#define MAX_Y           ( 1000 )
#define MAX_TIME        ( 300 )
#define MAX_EXEC_TIME   ( 3500 )
#define NUM_PARCEL      ( 30 )
#define RADIUS          ( 4 )

#define MULTIPLIER      ( 12 )
#define MIN_COST        ( 5000 )
#define PROPORTION      ( 1.0 )

#define BOUND_OF_TIME   ( 1500 )

#define NULL_RIDER      ( -1 )
//#define DEBUG 1
#define UNITTEST 1
using namespace::std;

int gTime;
int gOrder2[2][2] = { { 0, 1 }, { 1, 0 } }; 
int gOrder3[6][3] = { { 0, 1, 2 },
                    { 0, 2, 1 },
                    { 1, 0, 2 },
                    { 1, 2, 0 },
                    { 2, 0, 1 },
                    { 2, 1, 0 } };

/******** struct Definition *******/
typedef struct ikuPoint
{
    float x;
    float y;
    int   mRider;
    int   mArrivalTime;
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
		int			 mCost;
} ikuInfo;

void randomGen( ikuInfo * aIkuInfo )
{
    int   i;
		float sCost;

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
				
				sCost = length( aIkuInfo[i].mStart, aIkuInfo[i].mEnd ) * MULTIPLIER;
				if ( sCost < MIN_COST )
				{
						aIkuInfo[i].mCost = MIN_COST;
			  }
				else
				{
						aIkuInfo[i].mCost = sCost;
				}
    } 
}
void printPos( ikuPoint  a )
{
    cout << "( " << a.x << ", " << a.y << ") rider : " <<
            a.mRider << endl;
}

void print( ikuInfo a )
{
    int sTime;
    cout << "startPos : (" << a.mStart.x  << ", "
         << a.mStart.y  << ") | endPos : ("
         << a.mEnd.x    << ", "
         << a.mEnd.y    << ") | Time = "
         << a.mReqTime  << " | COST = $"
				 << a.mCost     << " | ";
         
    if ( ( a.mStart.mRider == NULL_RIDER ) ||
         ( a.mEnd.mRider == NULL_RIDER ) )
    {
        cout << " State : Not Delivered | " << endl;   
    }
    else
    {
        cout << " State : Delivered | ";
        if ( a.mStart.mArrivalTime > a.mEnd.mArrivalTime )
            sTime = a.mStart.mArrivalTime;
        else
            sTime = a.mEnd.mArrivalTime;
        
        cout << " Time : " << sTime << endl;
    }
}

bool compareTime( ikuInfo a, ikuInfo b ) 
{ 
    return ( a.mReqTime < b.mReqTime ); 
}
//////////////////////////////////////////////////////

typedef struct ikuRider
{
    ikuPoint               mPos;
    std::vector<ikuPoint*> mNodes;
    std::vector<ikuPoint*> mTmpNodes;
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
            aRider->mNodes.at(0)->mArrivalTime = gTime;
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
                                                ikuPoint             aPos,
                                                int                  *isValid)
{
    std::vector<ikuInfo>::iterator sClosestInfo;
    int  sIsValid = 0;

    if ( aCurInfo->size() == 0 )
    {
        *isValid = 0;
        return sClosestInfo;
    }
    else
    {
        sIsValid = 1;
        sClosestInfo = aCurInfo->begin();

        for ( std::vector<ikuInfo>::iterator it = aCurInfo->begin() ; 
                it != aCurInfo->end() ;
                ++it )
        {
            if ( length( sClosestInfo->mStart, aPos ) >
                    length( it->mStart, aPos ) )
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

float lengthOfPath( std::vector<ikuPoint*> *aPath )
{
    int i;
    float sLengthOfPath = 0;

    for ( i = 0 ; i < aPath->size() - 1 ; i++ )
    {
        sLengthOfPath += length( *(aPath->at(i)), 
                                 *(aPath->at(i+1)) );
    }

    return sLengthOfPath;
}

int getIndex( std::vector<ikuPoint*> * aVecArr,
              ikuPoint               * aPoint )
{
    int k;

    for ( k = 0 ; k < aVecArr->size() ; k++ )
    {
        if ( aVecArr->at(k) == aPoint )
        {
            return k;
        }
    }

    cout << "invalid Index" << endl;
    
    return -1;
}

void getBestPath2( std::vector<ikuPoint*> *aTmpPos, ikuPoint aRiderPos )
{
    std::vector<ikuPoint*> sTmpPos;
    std::vector<ikuPoint*> sBestPos;
    int i,j,k,l;
    int sStartIdx;
    int sStartIdx2;

    sTmpPos.reserve(10);
    sBestPos.reserve(10);

    for ( i = 0 ; i < 2 ; i++ )
    {
        sTmpPos.clear();
        
        // setting up startPos
        for ( j = 0 ; j < 2 ; j++ )
        {
            sTmpPos.push_back( aTmpPos->at( 2*gOrder2[i][j] ) ); 
        }

        // get First EndNode Startpoint.
        sStartIdx = getIndex( &sTmpPos, aTmpPos->at( 2*gOrder2[i][0] ) )
                    + 1;
        
        for ( k = sStartIdx ; k <= sTmpPos.size() ; k++ )
        {
            sTmpPos.insert( sTmpPos.begin() + k,
                            aTmpPos->at( 2*gOrder2[i][0] + 1 ) ); 

            // get Second EndNode Startpoint.
            sStartIdx2 = getIndex( &sTmpPos, aTmpPos->at( 2*gOrder2[i][1] ) )
                         + 1;
            for ( l = sStartIdx2 ; l <= sTmpPos.size() ; l++ )
            {
                sTmpPos.insert( sTmpPos.begin() + l,
                                aTmpPos->at( 2*gOrder2[i][1] + 1 ) ); 

                // compare with best path
                if ( ( sBestPos.size() == 0 ) ||
                        ( lengthOfPath( &sTmpPos ) + length( *sTmpPos.at(0), aRiderPos )
                        < lengthOfPath( &sBestPos ) + length( *sBestPos.at(0), aRiderPos ) ) )
                {
                    sBestPos.clear();
                    sBestPos.assign( sTmpPos.begin(), sTmpPos.end() );
                }
                sTmpPos.erase( sTmpPos.begin() + l );

            }
            sTmpPos.erase( sTmpPos.begin() + k );
        }
    }
    
    aTmpPos->clear();
    aTmpPos->assign( sBestPos.begin(), sBestPos.end() );
}
 
void getBestPath3( std::vector<ikuPoint*> *aTmpPos, ikuPoint aRiderPos )
{
    std::vector<ikuPoint*> sTmpPos;
    std::vector<ikuPoint*> sBestPos;
    int i,j,k,l,k2;
    int sStartIdx;
    int sStartIdx2;
    int sStartIdx3;

    sTmpPos.reserve(10);
    sBestPos.reserve(10);

    for ( i = 0 ; i < 6 ; i++ )
    {
        sTmpPos.clear();
        
        // setting up startPos
        for ( j = 0 ; j < 3 ; j++ )
        {
            sTmpPos.push_back( aTmpPos->at( 2*gOrder3[i][j] ) ); 
        }

        // get First EndNode Startpoint.
        sStartIdx = getIndex( &sTmpPos, aTmpPos->at( 2*gOrder3[i][0] ) )
                    + 1;
        
        for ( k = sStartIdx ; k <= sTmpPos.size() ; k++ )
        {
            sTmpPos.insert( sTmpPos.begin() + k,
                            aTmpPos->at( 2*gOrder3[i][0] + 1 ) ); 

            // get Second EndNode Startpoint.
            sStartIdx2 = getIndex( &sTmpPos, aTmpPos->at( 2*gOrder3[i][1] ) )
                         + 1;
            for ( l = sStartIdx2 ; l <= sTmpPos.size() ; l++ )
            {
                sTmpPos.insert( sTmpPos.begin() + l,
                                aTmpPos->at( 2*gOrder3[i][1] + 1 ) ); 

                // get Third EndNode Startpoint.
                sStartIdx3 = getIndex( &sTmpPos, aTmpPos->at( 2*gOrder3[i][2] ) )
                             + 1;

                for ( k2 = sStartIdx3 ; k2 <= sTmpPos.size() ; k2++ )
                {
                    sTmpPos.insert( sTmpPos.begin() + k2,
                                    aTmpPos->at( 2*gOrder3[i][2] + 1 ) ); 

                    // compare with best path
                    if ( ( sBestPos.size() == 0 ) ||
                            ( lengthOfPath( &sTmpPos ) + length( *sTmpPos.at(0), aRiderPos )
                              < lengthOfPath( &sBestPos ) + length( *sBestPos.at(0), aRiderPos ) ) )
                    {
                        sBestPos.clear();
                        sBestPos.assign( sTmpPos.begin(), sTmpPos.end() );
                    }

                    sTmpPos.erase( sTmpPos.begin() + k2 );
                }

                sTmpPos.erase( sTmpPos.begin() + l );

            }
            sTmpPos.erase( sTmpPos.begin() + k );
        }
    }
    
    aTmpPos->clear();
    aTmpPos->assign( sBestPos.begin(), sBestPos.end() );
}
                  

void newAlgorithm( std::vector<ikuInfo> * aCurInfo,
                   std::vector<ikuInfo> * aAllocInfo,
                   ikuRider             * aRider )
{
    std::vector<ikuInfo>::iterator sClosestInfo;
    std::vector<ikuInfo>::iterator sInfo;
    int   sIsValid;
    std::vector<ikuPoint*> sTmpPosition;
    std::vector<ikuPoint*> sBestPosition;

    sTmpPosition.reserve(10);
    sBestPosition.reserve(10);

    if ( aRider->mNodes.empty() ) /* A algorithm */
    {
        sClosestInfo = getClosestInfo( aCurInfo, aRider->mPos, &sIsValid);
        if ( sIsValid != 0 )
        {
// 1. Get Closest parcel
            aAllocInfo->push_back(*sClosestInfo);
            aCurInfo->erase(sClosestInfo);
            
            sTmpPosition.push_back(&(aAllocInfo->back().mStart));
            sTmpPosition.push_back(&(aAllocInfo->back().mEnd));
// 2. Get second parcel
            sClosestInfo = getClosestInfo( aCurInfo, 
                                           *(sTmpPosition.at(1)), 
                                           &sIsValid );

            if ( sIsValid != 0 )
            {
                aAllocInfo->push_back(*sClosestInfo);
                aCurInfo->erase(sClosestInfo);
                
                sTmpPosition.push_back(&(aAllocInfo->back().mStart));
                sTmpPosition.push_back(&(aAllocInfo->back().mEnd));

// 3. Get Third parcel
                sClosestInfo = getClosestInfo( aCurInfo, *(sTmpPosition.at(1)), &sIsValid );

                if ( sIsValid != 0 )
                {
                    aAllocInfo->push_back(*sClosestInfo);
                    aCurInfo->erase(sClosestInfo);

                    sTmpPosition.push_back(&(aAllocInfo->back().mStart));
                    sTmpPosition.push_back(&(aAllocInfo->back().mEnd));
                }
            }
        }
// 4. 
        if ( sTmpPosition.size() == 0 )
        {
           /* Nothing to do */ 
        }
        else if ( sTmpPosition.size() == 2 )
        {
            aRider->mNodes.assign( sTmpPosition.begin(), sTmpPosition.end() );
        }
        else if ( sTmpPosition.size() == 4 )
        {
            sBestPosition.clear();
            sBestPosition.assign( sTmpPosition.begin(), sTmpPosition.end() );
            getBestPath2( &sBestPosition, aRider->mPos ); 
            
            if ( lengthOfPath( &sBestPosition ) - length( *sTmpPosition.at(0), *sTmpPosition.at(1) )
                 < BOUND_OF_TIME * VELOCITY )
            {
                cout << "2묶음배송!" << endl;
                aRider->mNodes.assign( sBestPosition.begin(), sBestPosition.end() );
            }
            else
            {
                aRider->mNodes.assign( sTmpPosition.begin(), sTmpPosition.begin() + 2 );
                //allocInfo에서 빼서 다시 cur Info에 넣어줘야지...
                aCurInfo->push_back( *(aAllocInfo->end()-1) );
                aAllocInfo->erase( aAllocInfo->end()-1 );
            }
        }
        else if ( sTmpPosition.size() == 6 )
        {
            sBestPosition.clear();
            sBestPosition.assign( sTmpPosition.begin(), sTmpPosition.end() );
            getBestPath3( &sBestPosition, aRider->mPos ); 
            
            if ( lengthOfPath( &sBestPosition ) - length( *sTmpPosition.at(0), *sTmpPosition.at(1) )
                 < 2 * BOUND_OF_TIME * VELOCITY )
            {
                cout << "3묶음배송!" << endl;
                aRider->mNodes.assign( sBestPosition.begin(), sBestPosition.end() );
            }
            else
            {
                aRider->mNodes.assign( sTmpPosition.begin(), sTmpPosition.begin() + 2 );
                //allocInfo에서 빼서 다시 cur Info에 넣어줘야지...
                aCurInfo->push_back( *(aAllocInfo->end()-2) );
                aCurInfo->push_back( *(aAllocInfo->end()-1) );
                aAllocInfo->erase( aAllocInfo->end()-1 );
                aAllocInfo->erase( aAllocInfo->end()-1 );
            }
        }
        else
        {
            cout << "FUCKING ERROR!!!" << endl;
        }
    }
    else /* B Algorithm : 혼란가중! */
    {
        /* Nothing to do */
    }
    calculateNextPosition( aRider );
}

void oldAlgorithm( std::vector<ikuInfo> * aCurInfo,
                   std::vector<ikuInfo> * aAllocInfo,
                   ikuRider             * aRider )
{
    std::vector<ikuInfo>::iterator sClosestInfo;
    int   sIsValid;
    if ( aRider->mNodes.empty() )
    {
        sClosestInfo = getClosestInfo( aCurInfo, aRider->mPos, &sIsValid);
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
    int sSum;
/* Step 1. Generate and sort data set. */
    randomGen(sIkuInfo);
//// Vector
    std::vector<ikuInfo> sParcelInfoArr( sIkuInfo, sIkuInfo + NUM_PARCEL );
    
    std::vector<ikuInfo> sCurInfo;
    std::vector<ikuInfo> sCurInfo2;

    std::vector<ikuInfo> sAllocInfo;
    std::vector<ikuInfo> sAllocInfo2;

    sAllocInfo.reserve(NUM_PARCEL);
    sAllocInfo2.reserve(NUM_PARCEL);
    sCurInfo.reserve(NUM_PARCEL);
    sCurInfo2.reserve(NUM_PARCEL);

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
    sClosestInfo = getClosestInfo( &sParcelInfoArr, sRider1.mPos, &a );
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
        gTime = i;
        newAlgorithm( &sCurInfo,
                      &sAllocInfo,
                      &sRider1 );

        oldAlgorithm( &sCurInfo2, 
                      &sAllocInfo2,
                      &sRider2 );
    }
    cout << "-------- Rider1 Result ---------" << endl;
    for ( std::vector<ikuInfo>::iterator it = sAllocInfo.begin();
          it != sAllocInfo.end(); 
          ++it )
    {
        print(*it);
    }

    sSum = 0;
    for ( std::vector<ikuInfo>::iterator it = sAllocInfo.begin();
          it != sAllocInfo.end();
          ++it )
    {
        sSum += it->mCost;
    }
    cout << "Total cost : " << sSum * PROPORTION << endl;
    cout << "Rider1 Pos : " << sRider1.mPos.x << ", " << sRider1.mPos.y << endl;
    cout << "-------- Rider2 Result ---------" << endl;
    for ( std::vector<ikuInfo>::iterator it = sAllocInfo2.begin();
          it != sAllocInfo2.end(); 
          ++it )
    {
        print(*it);
    }
    cout << "Rider2 Pos : " << sRider2.mPos.x << ", " << sRider2.mPos.y << endl;
    sSum = 0;
    for ( std::vector<ikuInfo>::iterator it = sAllocInfo.begin();
          it != sAllocInfo.end();
          ++it )
    {
        sSum += it->mCost;
    }
    cout << "Total cost : " << sSum * PROPORTION << endl;
    return 0;
}
