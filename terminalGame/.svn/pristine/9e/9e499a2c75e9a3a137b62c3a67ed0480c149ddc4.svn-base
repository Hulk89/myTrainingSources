#include <stdio.h>
#include <termios.h>
#include <unistd.h>

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

int main()
{
    char Key;
    printf("Press any key to continue.\n");
    Key = mygetch();
    printf("Key : %c, Bye.\n", Key);
}
