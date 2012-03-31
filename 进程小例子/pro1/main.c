#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(void)
{
	pid_t pid;

	pid = fork();
	if(pid < 0)
	{
		perror("fork");
		exit(1);
	}
	else if(pid == 0)
	{
		int i = 0;
		for(i=0; i<3; i++)
		{
			if(i == 5)
			{
				printf("This is the child\n");
			}
			printf("This is child\n");
			sleep(1);
		}
		exit(9);
	}
	else
	{
		int stat_val;
		waitpid(pid, &stat_val, 0);
		if(WIFEXITED(stat_val))
		{
			printf("exit code:%d\n", WEXITSTATUS(stat_val));
		}
		else if(WIFSIGNALED(stat_val))
		{
			printf("signal num:%d\n", WTERMSIG(stat_val));
		}
	}
	return 0;
}
