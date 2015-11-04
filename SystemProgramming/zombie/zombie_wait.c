#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>


int main()
{
    int pid;
    int status;
    int spid;
    pid = fork();

    if (pid == 0)
    {
        sleep(5);
        printf("I will be back %d\n", getpid());
        return 1;
    }

    else if(pid > 0)
    {
        printf("Im parent %d\n", getpid());
        printf("Press any key and wait\n");
        getchar();
        // �ڽ����μ����� wait �Ѵ�. 
        // �ڽ����μ����� ������´� status �� ���� �޾ƿ´�. 
        spid = wait(&status);
        printf("�ڽ����μ��� wait ���� \n");
        // �ڽ����μ����� PID, ���ϰ�, �������(��������Ȥ�� ����������)�� 
        // ���´�.
        printf("PID         : %d\n", spid);
        printf("Exit Value  : %d\n", WEXITSTATUS(status));
        printf("Exit Stat   : %d\n", WIFEXITED(status));
    }
    else
    {
        perror("fork error :");
    }
    return 0;
}
