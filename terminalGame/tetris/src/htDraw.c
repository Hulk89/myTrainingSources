#include "htDraw.h"
#include "htBlock.h"

char gBlocks[3] = { '[',' ',']' };
char gEmpty[3]  = { ' ','*',' ' };
char gWall[3]   = { 'M','M','M' };
void draw()
{
    int i = 0;
    int j = 0;
   
    printf("\033[2J\033[1;1H");
    
    for ( i = 0 ; i < HEIGHT ; i++ )
    {
        for ( j = 0 ; j < WIDTH ; j++ )
        {
            if (  gForeground[i][j] == 1 )
            {
                printf( "%c%c%c",
                        gBlocks[0],
                        gBlocks[1],
                        gBlocks[2] );
            }
            else if ( gForeground[i][j] == 2 )
            {
                printf( "%c%c%c",
                        gWall[0],        
                        gWall[1],        
                        gWall[2] );    
            }
            else
            {
                printf( "%c%c%c",
                        gEmpty[0],
                        gEmpty[1],
                        gEmpty[2] );
            }
        }
        printf( "\n");
    }
    printf( "\n" );

}
