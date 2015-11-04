#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <pthread.h>


#define WIDTH  20
#define HEIGHT 10

int x = 0;
int y = 0;

int quit = 0;

void draw(char a)
{
    int i = 0;
    int j = 0;
   
    printf("\033[2J\033[1;1H");
    for ( i = 0 ; i < HEIGHT ; i++ )
    {
        for ( j = 0 ; j < WIDTH ; j++ )
        {
            if ( i == y && j == x )
            {
                printf("%c", a);
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

void* drawThr( void * ptr )
{
    char a = '@';
    
    int  i = 0;

    while ( !quit )
    {
        if ( i % 2 ==  0 )
            draw('@');
        else
            draw('#');
        i++;
        usleep(100000);
    }
    return 0;    
}

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
    char        Key;
    pthread_t   thr1;

    pthread_create( &thr1, NULL, drawThr,NULL );

    while ( 1 )
    {
        //get Input;
        Key = mygetch();

        if ( Key == 'q' )
        {
            quit = 1;
            break;
        }
        else
        {
            eventHandling( Key );   
        }
    }
    pthread_join( thr1, NULL);
    return 0;
}
