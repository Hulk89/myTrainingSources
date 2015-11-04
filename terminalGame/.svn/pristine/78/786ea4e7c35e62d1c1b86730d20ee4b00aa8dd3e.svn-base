#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#define WIDTH  10
#define HEIGHT 5

int x = 0;
int y = 0;

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

void draw()
{
    int i = 0;
    int j = 0;
    for ( i = 0 ; i < HEIGHT ; i++ )
    {
        for ( j = 0 ; j < WIDTH ; j++ )
        {
            if ( i == y && j == x )
            {
                printf("@");
            }
            else
            {
                printf("_");
            }
        }
        printf( "\n");
    }
    printf( "\n" );
}

void eventHandling( char Key )
{
    switch ( Key )
    {
        case 'a':
            if ( x > 0 )
                x--;
            break;
        case 's':
            if ( y < HEIGHT - 1 )
                y++;
            break;
        case 'd':
            if ( x < WIDTH - 1)
                x++;
            break;
        case 'w':
            if ( y > 0 )
                y--;
            break;
        default:
            break;
    }
}
int main()
{
    char Key;
    
    while ( 1 )
    {
        //get Input;
        Key = mygetch();

        if ( Key == 'q' )
            break;
        else
        {
            eventHandling( Key );   
            draw();
        }
    }
    return 0;
}
