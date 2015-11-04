#include "htBlock.h"
/*
0 0 0 0-
0 0 0 0
0 0 * 0
0 0 0 0+
-     +
*/
int gBlockMap[7][4][8] = {
{ { -2,-1,-1,-1, 0,-1, 1,-1 },
  {  0,-2, 0,-1, 0, 0, 0, 1 },
  { -2, 0,-1, 0, 0, 0, 1, 0 },
  { -1,-2,-1,-1,-1, 0,-1, 1 }
},// I
{ { -1,-1,-1, 0, 0, 0, 1, 0 },
  {  1,-1, 0,-1, 0, 0, 0, 1 },
  { -1, 0, 0, 0, 1, 0, 1, 1 },
  { -1, 1, 0, 1, 0, 0, 0,-1 }
},// J
{ { -1, 0, 0, 0, 1, 0, 1,-1 },
  {  0,-1, 0, 0, 0, 1, 1, 1 },
  { -1, 1,-1, 0, 0, 0, 1, 0 },
  { -1,-1, 0,-1, 0, 0, 0, 1 }
},// L
{ {  0,-1, 1,-1, 0, 0, 1, 0 },
  {  0,-1, 1,-1, 0, 0, 1, 0 },
  {  0,-1, 1,-1, 0, 0, 1, 0 },
  {  0,-1, 1,-1, 0, 0, 1, 0 }
},// O
{ { -1, 0, 0, 0, 0,-1, 1,-1 },
  {  0,-1, 0, 0, 1, 0, 1, 1 },
  { -1, 1, 0, 1, 0, 0, 1, 0 },
  { -1,-1,-1, 0, 0, 0, 0, 1 }
},//S
{ { -1, 0, 0, 0, 0,-1, 1, 0 },
  {  0,-1, 0, 0, 0, 1, 1, 0 },
  { -1, 0, 0, 0, 1, 0, 0, 1 },
  { -1, 0, 0,-1, 0, 0, 0, 1 }
},// T
{ { -1,-1, 0,-1, 0, 0, 1, 0 },
  {  0, 0, 0, 1, 1,-1, 1, 0 },
  { -1, 0, 0, 0, 0, 1, 1, 1 },
  { -1, 0,-1, 1, 0, 0, 0,-1 }
}//Z
};

void htInitBlock( htBlock *aBlock, blockShape aShape )
{
    int i = 0;

    aBlock->mShape = aShape;
    
    aBlock->mPosition.x = WIDTH/2;
    aBlock->mPosition.y = 0;
    aBlock->mRotation = 0;
    
    for ( i = 0 ; i < 4 ; i++ )
    {
        aBlock->mFill[i].x = gBlockMap[aShape][0][2*i];            
        aBlock->mFill[i].y = gBlockMap[aShape][0][2*i+1];            
    }

}

void htRotation( htBlock *aBlock, int aRotation )
{
    int     sAbsRot;
    htPos   sRelFill[4];
    int     i;
    int     sCollisionResult;

    if ( aRotation == 1 )
    {
        sAbsRot = ( aBlock->mRotation + 1 ) % 4;
    }
    else
    {
        sAbsRot = ( aBlock->mRotation + 3 ) % 4;
    }

    for ( i = 0 ; i < 4 ; i++ )
    {
        sRelFill[i].x = 
            gBlockMap[aBlock->mShape][sAbsRot][2 * i];
        sRelFill[i].y = 
            gBlockMap[aBlock->mShape][sAbsRot][2 * i + 1];
    }

    sCollisionResult = htCollisionDetection( aBlock, sRelFill );

    if ( sCollisionResult == 0 )
    {
        aBlock->mRotation = sAbsRot;
        for ( i = 0 ; i < 4 ; i++ )
        {
            aBlock->mFill[i].x = sRelFill[i].x;
            aBlock->mFill[i].y = sRelFill[i].y;
        }
    }
    else
    {
        /* Nothing to do */
    }
}

int htCollisionDetection( htBlock *aBlock, htPos *aRelFill )
{
    htPos   sAbsFill[4];
    int     i;

    for ( i = 0 ; i < 4 ; i++ )
    {
        sAbsFill[i].x = aRelFill[i].x + aBlock->mPosition.x;
        sAbsFill[i].y = aRelFill[i].y + aBlock->mPosition.y;
    }
    for ( i = 0 ; i < 4 ; i++ )
    {
        if ( gBackground[sAbsFill[i].y][sAbsFill[i].x] != 0 )
        {
            return -1;
        }
    }
    return 0;
}










