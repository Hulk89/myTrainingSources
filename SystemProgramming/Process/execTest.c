#include <unistd.h>

int main( int argc, char * argv )
{
    execl( "/bin/ls", "ls", "-al", NULL );
    return 0;
}
