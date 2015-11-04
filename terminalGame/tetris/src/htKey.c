#include "htKey.h"
#include "htBlock.h"
#include "htDraw.h"

int mygetch ( void ) 
{
    int ch;
    struct termios oldt, newt;

    tcgetattr ( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr ( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr ( STDIN_FILENO, TCSANOW, &oldt );

    return ch;
}

void eventHandling( char Key, htBlock *aBlock )
{
    pthread_mutex_lock( &(aBlock->mMtx) );
    switch ( Key )
    {
        case 'a':
            htRotation( aBlock, -1 );
            draw();
            break;
        case 's':
            break;
        case 'd':
            htRotation( aBlock, 1 );
            draw();
            break;
        case 'w':
            break;
        default:
            break;
    }
    pthread_mutex_unlock( &(aBlock->mMtx) );
}

