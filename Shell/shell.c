#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#define chop(str) str[strlen(str)-1]=0x00;

int main(int argc, char **argv)
{
	char buf[256];
	printf("Shell\n");
	int pid;
	while(1)
	{
		printf("[HULK_SHELL]");
		fgets(buf,255,stdin);
		chop(buf); // chop �� ����
		if(strncmp(buf,"quit",4)==0)
		{
			printf("Good bye");
			exit(0);
		}
		if(access(buf, X_OK)==0)
		{
			pid = fork();
			if(pid < 0)
			{
			    fprintf(stderr,"Command error!\n\n");
			}
			if(pid == 0)
			{
			    if(execl(buf,buf,NULL)==-1)
			    fprintf(stderr,"Command ERROR!\n\n");
			    exit(0);
			}
			if(pid > 0) //��� ���� 0���� ũ��
			{ 
			    int stat;
				fprintf(stdout,"Command started...\n");
			    waitpid(pid, &stat, WUNTRACED);
			}
		}
		else // �׷��� ������ �������...
		{
			fprintf(stderr,"Command Not Found! \n\n");
		}
	}
}
