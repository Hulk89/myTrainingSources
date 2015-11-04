#include <iostream>
#include <list>
#include <cmath>

using namespace std;

/* structure for vector */
typedef struct vec2
{
    float x;
    float y;
} vec2;

/* function declaration */
void pushList( list<vec2> *aList, float x, float y );
bool isObstacle( vec2* src, vec2* dst, list<vec2>* aList );
void initPocketList( list<vec2> * aList );
void printList( list<vec2>* aList );
float innerProduct( vec2* aVec1, vec2* aVec2 );
bool isInBoundary( vec2* aCueBall, vec2* aTarBall, vec2* aObsBall );
vec2 getGoalPosition( vec2* aTar, vec2* aPoc );

int main()
{
    float sTmp;
    int   sNumOfObstacle;
    int   i;
    bool  sIsShotExist = false;
    vec2  sCueBall;
    vec2  sTargetBall;
    vec2  sGoalPosition;
    vec2       sTmpVec;
    list<vec2> sGoalList;
    list<vec2> sObstacleList;
    list<vec2> sPocketList;

    std::ios::sync_with_stdio(false);

    initPocketList( &sPocketList );

    do
    {
        // Get Cue Ball, Target Ball position
        cin >> sTmp;
        if ( sTmp == 0 )
        {
            break;
        }
        else
        {
            cin >> sCueBall.y >> sTargetBall.x >> sTargetBall.y;
            sCueBall.x = sTmp;
        }

        // Get Obstacle Ball Position
        cin >> sNumOfObstacle;

        for ( i = 0 ; i < sNumOfObstacle ; i++ )
        {
            cin >> sTmpVec.x >> sTmpVec.y;
            pushList( &sObstacleList, sTmpVec.x, sTmpVec.y );
        }

        // Logic start here
        sIsShotExist = false;
        i = 1;
        for ( list<vec2>::iterator sPocketIter = sPocketList.begin() ;
              sPocketIter != sPocketList.end() ;
              sPocketIter++ )
        {
            // 1. isObstacle( targetBall, pocket[i], obsArray ) for all i
            if ( isObstacle( &sTargetBall, &*sPocketIter, &sObstacleList ) == false )
            {
            // 2. for available pocket, get goal position of cueball
                sGoalPosition = getGoalPosition( &sTargetBall, &*sPocketIter );
                sGoalPosition.x = sGoalPosition.x + sTargetBall.x;
                sGoalPosition.y = sGoalPosition.y + sTargetBall.y;

            // 3. isObstacle( cueBall, goalPosition, obsArray + targetBall )
                sObstacleList.push_back( sTargetBall );
                if ( isObstacle( &sCueBall, &sGoalPosition, &sObstacleList ) == false )
                {
                    sIsShotExist = true;
            // 4. print result
                    cout << i << " ";;
                }
                sObstacleList.pop_back();
            }

            i++;
        }
        if ( sIsShotExist == true )
        {
            cout << endl;
        }
        else
        {
            cout << "no shot" << endl;
        }
        while ( !sObstacleList.empty() )
        {
            sObstacleList.pop_back();
        }
    } while ( 1 );

    return 0;
}

bool isObstacle( vec2* src, vec2* dst, list<vec2>* aList )
{
    float sDenom;
    float sNumer;

    for ( list<vec2>::iterator sIter = aList->begin() ;
          sIter != aList->end() ;
          sIter++ )
    {
        if ( isInBoundary( src, dst, &*sIter ) == true )
        {
            sDenom = sqrt( pow( (src->x - dst->x), 2 ) +
                           pow( (src->y - dst->y), 2 ) );
            sNumer = fabs( ( dst->y - src->y )*( sIter->x - src->x ) - 
                           ( dst->x - src->x )*( sIter->y - src->y ) );
            if ( sNumer/sDenom < 2 ) 
            {
                return true;
            }
        }
    }
    return false;
}

float innerProduct( vec2* aVec1, vec2* aVec2 )
{
    return aVec1->x*aVec2->x + aVec1->y*aVec2->y;
}

bool isInBoundary( vec2* aCueBall, vec2* aTarBall, vec2* aObsBall )
{
    vec2 sCmp1;
    vec2 sCmp2;
    vec2 sCmpObs1;
    vec2 sCmpObs2;
    bool sResult = false;
    
    sCmp1.x = aCueBall->x - aTarBall->x;
    sCmp1.y = aCueBall->y - aTarBall->y;
    sCmpObs1.x = aObsBall->x - aTarBall->x;
    sCmpObs1.y = aObsBall->y - aTarBall->y;

    sCmp2.x = aTarBall->x - aCueBall->x;
    sCmp2.y = aTarBall->y - aCueBall->y;
    sCmpObs2.x = aObsBall->x - aCueBall->x;
    sCmpObs2.y = aObsBall->y - aCueBall->y;

    if ( ( innerProduct( &sCmp1, &sCmpObs1 ) >= 0 ) && 
         ( innerProduct( &sCmp2, &sCmpObs2 ) >= 0 ) )
    {
        sResult = true;
    }
    else
    {
        sResult = false;
    }

    return sResult;
}

vec2 getGoalPosition( vec2* aTar, vec2* aPoc )
{
    vec2  sGoalPos;
    float sDenom;

    sGoalPos.x = aTar->x - aPoc->x;
    sGoalPos.y = aTar->y - aPoc->y;

    sDenom = sqrt( pow( sGoalPos.x, 2 ) + pow( sGoalPos.y, 2 ) );

    sGoalPos.x = sGoalPos.x / sDenom * 2;
    sGoalPos.y = sGoalPos.y / sDenom * 2;

    return sGoalPos;
}

void initPocketList( list<vec2> * aList )
{
    pushList( aList, 0, 0 );
    pushList( aList, 54, 0 );
    pushList( aList, 108, 0 );
    pushList( aList, 0, 54 );
    pushList( aList, 54, 54 );
    pushList( aList, 108, 54 );
}

void pushList( list<vec2> *aList, float x, float y )
{
    vec2 sTmpVec;

    sTmpVec.x = x;
    sTmpVec.y = y;
    aList->push_back( sTmpVec );
}

void printList( list<vec2>* aList )
{
    for ( list<vec2>::iterator iterPos = aList->begin() ;
          iterPos != aList->end() ;
          iterPos++ )
    {
        cout << "( " << iterPos->x << ", " << iterPos->y << " )" << endl;
    }
}
