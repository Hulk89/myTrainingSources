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
            if ( i != y || j != x )
            {
                printf("_");
            }
            else
            {
                printf("@");
            }
        }
        printf( "\n");
    }
    printf( "\n" );
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
            switch ( Key )
            {
                case 'a':
                    x--;
                    break;
                case 's':
                    y++;
                    break;
                case 'd':
                    x++;
                    break;
                case 'w':
                    y--;
                    break;
                default:
                    break;

            }
            draw();
        }
    }
    return 0;
}
