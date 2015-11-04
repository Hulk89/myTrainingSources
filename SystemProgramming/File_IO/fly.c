#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#define MAXLEN 80

int main()
{
    int fd;
    int readn = 0;
    char buf[MAXLEN];
    struct stat sStat;
    
    fd = open( "ReadMe", O_RDONLY );
    if ( fd < 0 )
    {
        perror("file open error;");
        return 1;
    }

    stat( "ReadMe", &sStat );

    printf( "dev : %d\nino : %d\nuid : %d\n",
            sStat.st_dev, 
            sStat.st_ino, 
            sStat.st_uid );  


    memset( buf, 0x00, MAXLEN );

    while ( (readn = read( fd, buf, MAXLEN - 1 ) ) > 0 )
    {
        printf( "%s", buf );
        memset( buf, 0x00, MAXLEN );
    }
    return 0;
}

