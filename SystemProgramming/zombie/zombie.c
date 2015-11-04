#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main()
{
    int pid;
    int status;
    pid = fork();

    if (pid == 0)
    {
        sleep(5);
        printf("I will be back %d\n", getpid());
        exit(0);
    }
    else if(pid > 0)
    {
        printf("Im parent %d\n", getpid());
        printf("Press any key\n");
        getchar();
    }
    else
    {
        perror("fork error :");
    }
    return 0;
}

