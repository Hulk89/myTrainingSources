#include "htUpdate.h"
#include "htDraw.h"


void* updateThr( void * ptr )
{
    while ( !gQuit )
    {
        copyBuffer();
        draw();
        usleep(100000);
    }
    return 0;    
}

void copyTile( htBlock* aBlock )
{
    htPos   sFill[4];
    int     i = 0;

    pthread_mutex_lock( &(aBlock->mMtx) );
    for ( i = 0 ; i < 4 ; i++ )
    {
        sFill[i].x = aBlock->mFill[i].x + aBlock->mPosition.x;
        sFill[i].y = aBlock->mFill[i].y + aBlock->mPosition.y;
        printf( "%d %d\n", sFill[i].x, sFill[i].y);
        gForeground[sFill[i].y][sFill[i].x] = 1;
    }
    pthread_mutex_unlock( &(aBlock->mMtx) );
}
void copyBuffer()
{
    int i,j;

    for ( i = 0 ; i < HEIGHT ; i++ )
        for ( j = 0 ; j < WIDTH ; j++ )
            gForeground[i][j] = gBackground[i][j];

    copyTile( &gBlock );
}


