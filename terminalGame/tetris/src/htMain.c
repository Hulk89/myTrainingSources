#include "htDraw.h"
#include "htKey.h"
#include "htBlock.h"
#include "htupdate.h"

int     gQuit;
char    gBackground[HEIGHT][WIDTH];
char    gForeground[HEIGHT][WIDTH];
htBlock gBlock;

int main()
{
    char        Key;
    pthread_t   thr1;
    int         i;
    int         j;

    gQuit = 0;
    for ( i = 0 ; i < WIDTH ; i++ )
        for ( j = 0 ; j < HEIGHT ; j++ )
            if ( i < 1 || i >= WIDTH-1)
            {
                gBackground[j][i] = 2;
            }
            else if( j == HEIGHT-1 )
            {
                gBackground[j][i] = 2;
            }
            else
            {
                gBackground[j][i] = 0;
            }

    gBlock.mPosition.x = 5;
    gBlock.mPosition.y = 5;
    gBlock.mRotation = 0;
    gBlock.mShape = I;

    pthread_create( &thr1, NULL, updateThr,NULL );

    while ( 1 )
    {
        //get Input;
        Key = mygetch();

        if ( Key == 'q' )
        {
            gQuit = 1;
            break;
        }
        else
        {
            eventHandling( Key, &gBlock );
        }
    }
    pthread_join( thr1, NULL);
    return 0;
}
